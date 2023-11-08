#include "../include/ChatClient.h"



ChatClient::ChatClient() : keepRunning(false){}

ChatClient::~ChatClient(){}

void ChatClient::initialize(const char* serverIP, int serverPort, int listenPort){
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) 
    {
        perror("Failed to create socket");
        exit(EXIT_FAILURE);
    }

    //create thread
    recvThread = std::thread(&ChatClient::listenForMessagesThread,this);
    keepRunning = true;
    

    // Bind the client's socket to a specific port to listen for messages
    struct sockaddr_in listenAddr;
    memset(&listenAddr, 0, sizeof(listenAddr));
    listenAddr.sin_family = AF_INET;
    listenAddr.sin_addr.s_addr = INADDR_ANY;
    listenAddr.sin_port = htons(listenPort);
    if (bind(sockfd, (struct sockaddr*)&listenAddr, sizeof(listenAddr)) < 0) 
    {
        perror("Failed to bind client socket");
        exit(EXIT_FAILURE);
    }

    memset(&serverAddr, 0,sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    serverAddr.sin_port = htons(serverPort);

    struct timeval timeout;
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    if((setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout))) < 0){
        perror("Error setting socket options");
        exit(EXIT_FAILURE);
    }

} 


std::string ChatClient::listenForMessages(){
    char buffer[1024] = {0};
    struct sockaddr_in fromAddr;
    socklen_t len = sizeof(fromAddr);
    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&fromAddr, &len);
    if (n < 0)
    {
        if (errno != EAGAIN && errno != EWOULDBLOCK)
        {
            perror("Error receiving data");
        }
        return"";
    }

    buffer[n] = '\0';
    std::string recvMessage(buffer);
    std::cout << "Received reponse: " << recvMessage << " from server." << std::endl;
    return recvMessage;
    
}

void ChatClient::sendMessage(const char* message){
    sendto(sockfd, message, strlen(message), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
}


void ChatClient::shutdown(){
    // close the server
    // close(sockfd);
    // std::cout << "server shut down." << std::endl;

    keepRunning.store(false);
    if (recvThread.joinable())
    {
        recvThread.join();
    }
    if (sockfd != -1)
    {
        close(sockfd);
        sockfd = -1;
    }
    
    
}


std::string ChatClient::popMessage(){
    std::lock_guard<std::mutex> guard(msgMutex);
    if (messageQueue.empty())
    {
        return "";
    }
    std::string msg = messageQueue.front();
    messageQueue.pop();
    return msg;
    
}

void ChatClient::listenForMessagesThread(){
    while(keepRunning){
        std::string msg = listenForMessages();
        if (!msg.empty())
        {
            std::lock_guard<std::mutex> guard(msgMutex);
            messageQueue.push(msg);
            newMessageFlag = true;
            cv.notify_one();
        }
        
    }
}

void ChatClient::waitForNewMessage(){
    std::unique_lock<std::mutex> lock(msgMutex);
    cv.wait(lock, [this]{ return newMessageFlag; });
    newMessageFlag = false;
    
}

void ChatClient::resetNewMessageFlag(){
    std::lock_guard<std::mutex> guard(msgMutex);
    newMessageFlag = false;
}

bool ChatClient::hasMessages(){
    std::lock_guard<std::mutex> guard(msgMutex);
    return !messageQueue.empty();
}