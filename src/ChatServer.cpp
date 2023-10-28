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

void ChatServer::initialize(int port){
    //Create socket, bind it, etc
    sockfd = socket(AF_INET,SOCK_DGRAM,0);
    if (sockfd == -1)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    // set the server address structure
    struct sockaddr_in servaddr;
    memset(&servaddr, 0 , sizeof(servaddr));
    servaddr.sin_family = AF_INET; //IPv4
    servaddr.sin_addr.s_addr= INADDR_ANY; // listen on any interface
    servaddr.sin_port = htons(port);
    
    //bind the socket
    if(bind(sockfd, (struct sockaddr*)&servaddr,sizeof(servaddr)) < 0){
        perror("Fail to to bind socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }
    std::cout << "Server initialized and bound to port " << port << std::endl;
}

void ChatServer::listenForMessages(){
    // send a message to a client

    char buffer[1024];
    struct sockaddr_in cliaddr;
    socklen_t len = sizeof(cliaddr);

    int n = recvfrom(sockfd, buffer,sizeof(buffer),0, (struct sockaddr*)&cliaddr, &len);
    if (n < 0)
    {
        perror("Error receiving data");
        return;
    }

    buffer[n] = '\0'; // Null-terminate the received data
    std::cout << "Received message: " << buffer << " from client." << std::endl;

    // send a reponse back to the client
    const char * reponse = "Message received by server";
    sendto(sockfd,strlen(response),0,(struct sockaddr&)&cliaddr,len);    


}

void ChatServer::shutdown(){
    // close the server 
    close(sockfd);
    std::cout << "Server shut down. "<< std::endl;
}

int main(){
    //Register the signal handler
    signal(SIGINT, handleSignal);
    ChatServer server;
    server.initialize(8080);

    while(true){
        server.listenForMessages();

    }

    server.shutdown();
    return 0;
}


