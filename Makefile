# Compiler settings
CXX = g++
CXXFLAGS = -g -Wall -Wextra -std=c++17 -I$(SRC_DIR)/header `pkg-config --cflags sdl2`
LDFLAGS = `pkg-config --libs sdl2`

# Directory settings
SRC_DIR = SDLRotate
SRC_SUBDIR = $(SRC_DIR)/source
BUILD_DIR = build
OUTPUT_DIR = output

# Source files and object files
SOURCES = main.cpp Display.cpp FrameHandler.cpp Matrix4x4.cpp Mesh.cpp vectorTypes.cpp
OBJECTS = $(addprefix $(BUILD_DIR)/, $(SOURCES:.cpp=.o))

# Output executable name
TARGET = $(OUTPUT_DIR)/SDLRotate

# Debug information
$(info Sources: $(SOURCES))
$(info Objects: $(OBJECTS))
$(info Looking for source files in: $(SRC_SUBDIR))

# Default target
all: directories $(TARGET)

# Create necessary directories
directories:
	mkdir -p $(BUILD_DIR) $(OUTPUT_DIR)
	@echo "Current directory: $$(pwd)"
	@echo "Contents of source directory:"
	@ls -la $(SRC_SUBDIR)

# Link the program
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files
$(BUILD_DIR)/%.o: $(SRC_SUBDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -rf $(BUILD_DIR) $(OUTPUT_DIR)

# Phony targets
.PHONY: all clean directories 