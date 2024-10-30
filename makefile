# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I./src

# Target executable
TARGET = my_program

# Source files and object files
SRCS = main.cpp src/Tokenizer.cpp src/TreeBuilder.cpp  # List all source files with their paths
OBJDIR = obj
OBJS = $(OBJDIR)/main.o $(OBJDIR)/Tokenizer.o $(OBJDIR)/TreeBuilder.o

# Default target
all: $(TARGET)

# Link object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile .cpp files in src/ to .o files in obj/
$(OBJDIR)/%.o: %.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJDIR)/Tokenizer.o: src/Tokenizer.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c src/Tokenizer.cpp -o $(OBJDIR)/Tokenizer.o

$(OBJDIR)/TreeBuilder.o: src/TreeBuilder.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c src/TreeBuilder.cpp -o $(OBJDIR)/TreeBuilder.o

# Ensure obj directory exists
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Clean up object files and the executable
clean:
	rm -f $(OBJS) $(TARGET)
	rm -rf $(OBJDIR)

# Phony targets
.PHONY: all clean
