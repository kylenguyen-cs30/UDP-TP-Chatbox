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
#include <thread>
#include <mutex>
#include <atomic>
#include <queue>
#include <condition_variable>

class ChatServer
{
private:
    int sockfd;
    char buffer[1024];
    struct sockaddr_in servadd, cliaddr;
    std::thread recvThread;
    std::atomic<bool> keepRunning;
    std::mutex msgMutex;
    std::queue<std::string> messageQueue;
    std::condition_variable cv;

    bool newMessageFlag{false};
    void listenForMessagesThread(); // run by receiving thread

public:
    ChatServer();
    ~ChatServer();

    void initialize(int port);
    std::string listenForMessages();
    void sendMessage(const char *message);
    void shutdown();
    bool hasMessages();
    std::string popMessage();  // this method to get the next message


     //conditional variable
    void waitForNewMessage();
    void resetNewMessageFlag();
};


#endif // !CHATSERVER_H
