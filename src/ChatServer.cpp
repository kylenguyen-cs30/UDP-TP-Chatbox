#include "../include/ChatServer.h"
#include <signal.h>

volatile bool keepRunning = true;

void handleSignal(int signal){
    keepRunning = false;
}


ChatServer::ChatServer(){
    //Constructor
}

ChatServer::~ChatServer(){
    //Desconstructor
}

void ChatServer::initialize(int recvPort){
   // create socket
   sockfd = socket(AF_INET,SOCK_DGRAM, 0);
   if (sockfd == -1){
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
   }

   // set up the server address sutrcutre for receiving 
   struct sockaddr_in recvAddr;
   memset(&recvAddr , 0 , sizeof(recvAddr));
   recvAddr.sin_family = AF_INET; // IPv4
   recvAddr.sin_addr.s_addr = INADDR_ANY;
   recvAddr.sin_port = htons(recvPort);

   //bind the socket for receiving
   if(bind(sockfd, (struct sockaddr*)&recvAddr, sizeof(recvAddr)) < 0){
    perror("Fail to bind socket");
    close(sockfd);
    exit(EXIT_FAILURE);
   }

   std::cout << "Server initialized and bound to port " << recvPort << std::endl;
   
}

void ChatServer::listenForMessages(){
    char buffer[1024] = {0};
    struct sockaddr_in cliaddr;
    socklen_t  len = sizeof(cliaddr);

    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
    if (n < 0)
    {
        perror("Error receiving data");
        return;
    }

    buffer[n] = '\0'; // Null terminate the recevied data
    std::cout << "Received message: " << buffer << " from client. " << std::endl;

    // address to send a response back the client
    struct sockaddr_in sendAddr;
    sendAddr.sin_family = AF_INET;
    sendAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sendAddr.sin_port = htons(3514);

    const char * response = "Message recevied by server";
    sendto(sockfd,response, strlen(response), 0, (struct sockaddr*)&sendAddr,sizeof(sendAddr));
    
}

void ChatServer::sendMessage(const char* message){}

void ChatServer::shutdown(){
    // close the server 
    close(sockfd);
    std::cout << "Server shut down. "<< std::endl;
}

int main(){
    //Register the signal handler
    signal(SIGINT, handleSignal);
    
    ChatServer server;
    server.initialize(3515);

    while(keepRunning){
        server.listenForMessages();

    }

    server.shutdown();
    return 0;
}


