# Compiler
CXX = g++

# Compiler Flags
CXXFLAGS = -Wall -Wextra -std=c++11

# Target executable
TARGET = kruskals

# Source and object files
SRCS = kruskals.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Compile the main executable
$(TARGET): $(OBJS)
	@$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile the object files
%.o: %.cpp kruskals.h
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJS) $(TARGET)
