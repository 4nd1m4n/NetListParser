# -*- Makefile -*-

# Output file (binary for execution)
TARGET_EXEC ?= NetListParser.exc
# Arguments for make run configuration
COMMANDLINE_OPTIONS ?= -f "resources/OPV-ideal.exnet"
# Directory containing all source files
SRC_DIRS ?= ./quellcode
# Directory to put all build files . so git ignores them
BUILD_DIR ?= ./build

# It is not likely, that anything below this line has to be changed

# Find all source files in and in all subdirectorys of SRC_DIRS
SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
# Derive object names from found source file names and prepend their path by BUILD_DIR
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
# Derive dependencie names from found object file names
DEPS := $(OBJS:.o=.d)

# Find all subfolders of SRC_DIRS and set them as include directorys (pretend there might be include files)
#INC_DIRS := $(shell find $(SRC_DIRS) -type d)
#INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Find all header file paths of SRC_DIRS
INC_FILES := $(shell find $(SRC_DIRS) -name *.h -or -name *.hpp)
# Extract their path and uniquify it
INC_DIRS := $(sort $(dir $(INC_FILES)))
# Then set them as include flags by prepending all with -I prefix
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Compiler to use
CC = g++
# C compiler flags to set
CFLAGS = -c -Wall -std=c++11
# Linker flags to set
LDFLAGS =
# Cpp compiler flags to set
CPPFLAGS ?= $(INC_FLAGS) $(CFLAGS) -MMD -MP

# Build all
$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# C source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# C++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Build & Run Project
run: $(BUILD_DIR)/$(TARGET_EXEC)
	./$(BUILD_DIR)/$(TARGET_EXEC) $(COMMANDLINE_OPTIONS)

# If something seems wrong execute clean
.PHONY: clean

# Cleans all buildfiles
clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p