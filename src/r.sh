#!/bin/bash

# Compile the application
g++ gui.cpp -I../include $(wx-config --cxxflags --libs) -o chat_app

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the application..."
    ./chat_app
else
    echo "Compilation failed."
fi
