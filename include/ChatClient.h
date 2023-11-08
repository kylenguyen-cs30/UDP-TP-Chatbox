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
#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <condition_variable>

class ChatClient
{
private:
    int sockfd;
    char buffer[1024];
    struct sockaddr_in serverAddr;
    std::thread recvThread;
    std::atomic<bool> keepRunning;
    std::mutex msgMutex;
    std::queue<std::string> messageQueue;
    std::condition_variable cv;

    
    bool newMessageFlag{false};
    void listenForMessagesThread();
public:
    ChatClient(/* args */);
    ~ChatClient();

    void initialize(const char* serverIP,int port, int listenPort);
    std::string listenForMessages();
    void sendMessage(const char* message);
    void shutdown();
    bool hasMessages();
    std::string popMessage();

    //conditional variable
    void waitForNewMessage();
    void resetNewMessageFlag();
};


#endif // !CHATCLIENT_H
