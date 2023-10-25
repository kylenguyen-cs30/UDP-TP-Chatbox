#ifndef CHATSERVER_H
#define CHATSERVER_H

#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <stdio.h>
#include <iostream>
class ChatServer
{
private:
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servadd, cliaddr;
public:
    ChatServer();
    ~ChatServer();

    void initialize(int port);
    void listenForMessages();
    void sendMessage(const char* message);
    void shutdown();
};




#endif // !CHATSERVER_H
