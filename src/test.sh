#!/bin/bash

# Compilation flags for wxWidgets
WX_CFLAGS=$(wx-config --cxxflags)
WX_LIBS=$(wx-config --libs)

# Compile the client
echo "compile gui.cpp client_main.cpp ChatClient.cpp ChatServer.cpp to output test_chatapp_client"
g++ $WX_CFLAGS gui.cpp client_main.cpp ChatClient.cpp ChatServer.cpp $WX_LIBS -o test_chatapp_client -std=c++17

if [ $? -eq 0 ]; then 
    echo "Client compilation successful."
else
    echo "Client compilation failed"
    exit 1
fi

# Compile the server
echo "compile gui.cpp server_main.cpp ChatServer.cpp ChatClient.cpp to output test_chatapp_server"
g++ $WX_CFLAGS gui.cpp server_main.cpp ChatServer.cpp ChatClient.cpp $WX_LIBS -o test_chatapp_server -std=c++17

if [ $? -eq 0 ]; then
    echo "Server compilation successful."
else
    echo "Server compilation failed."
    exit 1
fi
