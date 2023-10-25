# Compiler
CXX = g++

# wxWidgets configuration
WX_CONFIG = wx-config

# Compiler and linker flags
CXXFLAGS = -I../include $(shell $(WX_CONFIG) --cxxflags)
LDFLAGS = $(shell $(WX_CONFIG) --libs)

# Source and target
SRC = src/gui.cpp
TARGET = chat_app

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f $(TARGET)
