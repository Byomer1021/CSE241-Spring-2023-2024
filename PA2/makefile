# Makefile for SparseVector and SparseMatrix assignment

# Compiler and compiler flags
CXX := g++
CPPFLAGS := -std=c++11
CXXFLAGS := -MMD
LDFLAGS :=

# Directories
SRC_DIR := .
OBJ_DIR := obj

# Source and object files
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)

# Target executable
TARGET := main.out

# Main target
all: $(TARGET)

# Rule to generate executable
$(TARGET): $(OBJ_FILES)
    $(CXX) $(LDFLAGS) -o $@ $^

# Rule to generate object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
    $(CXX) $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<

# Create object directory
$(OBJ_DIR):
    mkdir -p $(OBJ_DIR)

# Include dependencies
-include $(DEP_FILES)

# Clean rule
clean:
    rm -rf $(OBJ_DIR) $(TARGET)

# Phony target to avoid conflict with files named clean
.PHONY: clean
