# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./src -g -w

# Target executable
TARGET = my_program

# Source files and object files
SRCS = main.cpp src/*.cpp  # List all source files with their paths


# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Ensure obj directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up object files and the executable
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all clean