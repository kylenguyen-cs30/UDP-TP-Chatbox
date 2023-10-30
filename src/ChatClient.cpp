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
    
    

} 


void ChatClient::listenForMessages(){
    
}

void ChatClient::sendMessage(const char* message){

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
    while ()
    {
        server.listenForMessages();
    }
    server.shutdown();
    return 0;
}
