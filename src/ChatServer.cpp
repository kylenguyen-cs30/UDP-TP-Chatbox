#include "../include/ChatServer.h"
#include <signal.h>


// static volatile bool keepRunning = true;

// static void handleSignal(int signal){
//     std::cout << "Handle signal is called" << std::endl;
//     keepRunning = false;
// }


ChatServer::ChatServer() : keepRunning(false){
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

   // start the thread 
   recvThread = std::thread(&ChatServer::listenForMessagesThread,this);
   keepRunning = true;

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


   // set a timeout for recvfrom
   struct timeval timeout;
   timeout.tv_sec = 1; // 1 sec timeout
   timeout.tv_usec = 0;

   if(setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0){
    perror("Failed to set socket timeout");
    close(sockfd);
    exit(EXIT_FAILURE);
   }



   std::cout << "Server initialized and bound to port " << recvPort << std::endl;
   
}

void ChatServer::listenForMessagesThread(){
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




std::string ChatServer::listenForMessages(){
    char buffer[1024] = {0};
    struct sockaddr_in cliaddr;
    socklen_t  len = sizeof(cliaddr);

    int n = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
    if (n < 0)
    {
        if (errno != EAGAIN && errno != EWOULDBLOCK)
        {
            perror("Error receiving data");
            return"";
        }
        
    }

    buffer[n] = '\0'; // Null terminate the recevied data
    

    return std::string(buffer);
    
}

void ChatServer::sendMessage(const char* message){
    //destination address structure
    struct sockaddr_in destAddr;

    memset(&destAddr, 0,sizeof(destAddr));
    destAddr.sin_family = AF_INET;
    destAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    destAddr.sin_port = htons(3514);

    // send the message
    int bytesSent = sendto(sockfd, message, strlen(message), 0,(struct sockaddr*)&destAddr,sizeof(destAddr));
    if (bytesSent < 0)
    {
        perror("Error sending message");
    }else{
        std::cout << "Sent message: " << message << std::endl;
    }
    
}

std::string ChatServer::popMessage(){
    std::lock_guard<std::mutex> guard(msgMutex);
    if (messageQueue.empty())
    {
        return "";
    }
    std::string msg = messageQueue.front();
    messageQueue.pop();
    return msg;
}

void ChatServer::shutdown(){
    // close the server 
    // close(sockfd);
    // std::cout << "Server shut down. "<< std::endl;

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

void ChatServer::waitForNewMessage(){
    std::unique_lock<std::mutex> lock(msgMutex);
    cv.wait(lock, [this]{ return newMessageFlag; });
    newMessageFlag = false;
    
}

void ChatServer::resetNewMessageFlag(){
    std::lock_guard<std::mutex> guard(msgMutex);
    newMessageFlag = false;
}


bool ChatServer::hasMessages(){
    std::lock_guard<std::mutex> guard(msgMutex);
    return !messageQueue.empty();
}