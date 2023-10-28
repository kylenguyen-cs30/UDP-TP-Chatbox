# Compiler
CXX = g++

# wxWidgets configuration
WX_CONFIG = wx-config

# Compiler and linker flags
CXXFLAGS = -I../include $(shell $(WX_CONFIG) --cxxflags)
LDFLAGS = $(shell $(WX_CONFIG) --libs)

# Source and target
SRCS = src/gui.cpp src/main.cpp
TARGET = chat_app

all: $(TARGET)

# $(TARGET): $(SRC)
# 	$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET)

# clean:
# 	rm -f $(TARGET)


$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)

clean:
	rm -f $(TARGET)