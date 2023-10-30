#ifndef CHATCLIENT_H
#define CHATCLIENT_H
//include libraries
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <iostream>

class ChatClient
{
private:
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serverAddr;
public:
    ChatClient(/* args */);
    ~ChatClient();

    void initialize(const char* serverIP,int port, int listenPort);
    void listenForMessages();
    void sendMessage(const char* message);
    void shutdown();
};


#endif // !CHATCLIENT_H