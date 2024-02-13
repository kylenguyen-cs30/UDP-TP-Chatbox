
# CHAT APPLICATION 


## Project Structure 


- include/: Contains header files for the ChatClient, ChatServer, and GUI components.
- src/: Contains the implementation (.cpp files) of the ChatClient, ChatServer, GUI components, and main files for both the client and server.
- Makefile: A makefile to compile the project.
- Step by Step Setup Guide.docx: A document providing detailed setup instructions.
- readme.md: This readme file.
- wxWidgets-3.1.5.tar.bz2: The wxWidgets library needed to compile the GUI.


## Overview of Mutexes and Threads
- This application utilizes mutexes (std::mutex) and threads (std::thread) to handle concurrent operations in both the ChatClient and ChatServer components safely.

- Threads: Separate threads are spawned for listening to incoming messages. This ensures that the main thread, responsible for the GUI and user interactions, remains responsive. For instance, ChatClient::listenForMessagesThread and ChatServer::listenForMessagesThread run in their own threads, continuously listening for messages.

- Mutexes: Mutexes are used to protect shared resources, specifically the message queues (std::queue<std::string> messageQueue). When a new message arrives, it is pushed to the queue in a thread-safe manner using a mutex to prevent simultaneous access from other threads. This ensures data consistency and thread safety.

- Condition Variables: Used alongside mutexes to signal the arrival of new messages, allowing threads to wait for conditions (new messages) before proceeding. This mechanism helps in efficiently managing thread execution and resource utilization.

