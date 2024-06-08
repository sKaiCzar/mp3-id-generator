# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++11 -Wall -Wextra

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
BIN_DIR = bin

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))

# Executable name
EXEC = music_api

# Include directories
INC = -I$(INC_DIR)

# Linker flags
LDFLAGS = 

# Libraries
LIBS =

# Target: build executable
$(BIN_DIR)/$(EXEC): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(OBJS) $(LIBS) -o $@

# Target: compile object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

# Target: create directories
$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

# Target: clean object and executable files
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# Target: remove object files
cleanobj:
	rm -rf $(OBJ_DIR)/*

# Target: remove executable
cleanexec:
	rm -rf $(BIN_DIR)/$(EXEC)

# Phony targets
.PHONY: clean cleanobj cleanexec
