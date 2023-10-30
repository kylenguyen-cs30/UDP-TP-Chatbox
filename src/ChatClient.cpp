#include "../include/ChatClient.h"
#include <signal.h>

volatile bool keepRunning = true;

// handle incoming signal
void handleSignal(int signal){
    keepRunning = false;
}

ChatClient::ChatClient(){}

ChatClient::~ChatClient(){}

void ChatClient::initialize(int recvPort){
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1)
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in, recvAddr;
    memset(&recvAddr , 0, sizeof(recvAddr));
    recvAddr.sin_family = AF_INET;
    recvAddr.sin_addr.s_addr = INADDR_ANY;
    recvAddr.sin_port = htons(recvPort);

    //bind the socket for receving
    if(bind(sockfd, (struct sockaddr*)&recvAddr, sizeof(recvAddr)) < 0){
        perror("fail to bidn socket");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server initialized and bound to port" << recvPort << std::endl;
    

} 


void ChatClient::listenForMessages(){
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
    std::cout << "Received message: " << buffer << " from client. " << std::end;

    // address to send a response back the client
    struct sockaddr_in sendAddr;
    sendAddr.sin_addr = AF_INET;
    sendAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sendAddr.sin_port = htons(3514);

    const char * response = "Message recevied by server";
    sendto(sockfd,response, strlen(response), 0, (struct sockaddr*)&sendAddr,sizeof(sendAddr));
}

void ChatClient::sendMessage(){

}

void ChatClient::shutdown(){
    // close the server
    close(sockfd);
    std::cout << "server shut down." << std::endl;
}


int main(int argc, char const *argv[])
{
    //register the signal handler
    signal(SIGINT, handleSignal);
    ChatClient client;
    client.initialize(3515);
    while (true)
    {
        server.listenForMessages();
    }
    server.shutdown();
    return 0;
}
