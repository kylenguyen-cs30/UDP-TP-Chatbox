
# CHAT APPLICATION 


## Project Structure 

```
├── Makefile
├── chat_app
├── include
│   ├── ChatClient.h
│   ├── ChatServer.h
│   └── GUI.h
├── readme.md
├── src
│   ├── ChatClient.cpp
│   ├── ChatServer.cpp
│   ├── client_main.cpp
│   ├── gui.cpp
│   ├── launch.json
│   ├── server_main.cpp
│   ├── tasks.json
│   ├── test.sh
│   ├── test_chatapp_client
│   └── test_chatapp_server
└── wxWidgets-3.1.5.tar.bz2

3 directories, 17 files
```


- include/: Contains header files for the ChatClient, ChatServer, and GUI components.
- src/: Contains the implementation (.cpp files) of the ChatClient, ChatServer, GUI components, and main files for both the client and server.
- Makefile: A makefile to compile the project.
- Step by Step Setup Guide.docx: A document providing detailed setup instructions.
- readme.md: This readme file.
- wxWidgets-3.1.5.tar.bz2: The wxWidgets library needed to compile the GUI.

## Installation
- wxWidgets Setup: Ensure wxWidgets is installed and properly configured on your system. If not, refer to the wxWidgets-3.1.5.tar.bz2 archive included in the project for installation or download the latest version from the wxWidgets official website.

- Compilation: Use the provided Makefile to compile the application. Run the following command in the terminal:


```
make all
```
- Run: After successful compilation, you can start the server and client applications.

## Usage
- Server Mode: To start the application in server mode, run:

```
./chat_app --server
```
- Client Mode: To start the application in client mode, run:


```
./chat_app --client
```
- Ensure the server is running before starting a client. The default configuration uses localhost and predefined ports for communication.


## Overview of Mutexes and Threads
- This application utilizes mutexes (std::mutex) and threads (std::thread) to handle concurrent operations in both the ChatClient and ChatServer components safely.

- Threads: Separate threads are spawned for listening to incoming messages. This ensures that the main thread, responsible for the GUI and user interactions, remains responsive. For instance, ChatClient::listenForMessagesThread and ChatServer::listenForMessagesThread run in their own threads, continuously listening for messages.

- Mutexes: Mutexes are used to protect shared resources, specifically the message queues (std::queue<std::string> messageQueue). When a new message arrives, it is pushed to the queue in a thread-safe manner using a mutex to prevent simultaneous access from other threads. This ensures data consistency and thread safety.

- Condition Variables: Used alongside mutexes to signal the arrival of new messages, allowing threads to wait for conditions (new messages) before proceeding. This mechanism helps in efficiently managing thread execution and resource utilization.

