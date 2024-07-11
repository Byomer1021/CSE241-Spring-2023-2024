# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Target executable name
TARGET = catalog_manager

# Object files
OBJS = main.o CatalogManager.o

# Default rule
all: $(TARGET)

# Rule to link object files and create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule to compile main.cpp
main.o: main.cpp CatalogManager.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# Rule to compile CatalogManager.cpp
CatalogManager.o: CatalogManager.cpp CatalogManager.h
	$(CXX) $(CXXFLAGS) -c CatalogManager.cpp

# Clean up the build
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean
