# Makefile for Chat Application

# Compilation flags for wxWidgets
WX_CFLAGS := $(shell wx-config --cxxflags)
WX_LIBS := $(shell wx-config --libs)

# Compiler
CXX := g++

# Compiler options
CXXFLAGS := -std=c++17 $(WX_CFLAGS)
LDFLAGS := $(WX_LIBS)

# Targets
all: test_chatapp_client test_chatapp_server

test_chatapp_client: gui.cpp client_main.cpp ChatClient.cpp ChatServer.cpp
    @echo "Compiling the client application..."
    $(CXX) $(CXXFLAGS) gui.cpp client_main.cpp ChatClient.cpp ChatServer.cpp $(LDFLAGS) -o test_chatapp_client
    @echo "Client compilation successful."

test_chatapp_server: gui.cpp server_main.cpp ChatServer.cpp ChatClient.cpp
    @echo "Compiling the server application..."
    $(CXX) $(CXXFLAGS) gui.cpp server_main.cpp ChatServer.cpp ChatClient.cpp $(LDFLAGS) -o test_chatapp_server
    @echo "Server compilation successful."

clean:
    @echo "Cleaning up..."
    rm -f test_chatapp_client test_chatapp_server

.PHONY: all clean
