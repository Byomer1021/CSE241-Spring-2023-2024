# Variables to control Makefile operation
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Name of the executable to create
TARGET = robot_sim

# All .cpp files in this directory are considered sources
SOURCES = $(wildcard *.cpp)
# Automatically generate a list of object files
OBJECTS = $(SOURCES:.cpp=.o)

# The build target executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

# A rule to build .o files from .cpp files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean files created by the compiler
clean:
	rm -f $(OBJECTS) $(TARGET)
