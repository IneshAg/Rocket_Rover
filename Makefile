# Makefile for GPS Path Planning Rover Project
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2
TARGET = rover
SOURCES = main.cpp ublox_reader.cpp planning.cpp odometry.cpp gridmap.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
.PHONY: all clean build check

all: $(TARGET)

# Build the executable
$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

# Compile source files to object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build target (equivalent to make build)
build: $(TARGET)

# Check target (equivalent to make check)
check: $(TARGET)
	@echo "*** Success: ***"
	@echo "--------------------------------------------"

# Clean target (equivalent to make clean)
clean:
	del /Q $(OBJECTS) $(TARGET) 2>nul || echo "No files to delete"
	del /Q *.exe 2>nul || echo "No exe files to delete"

# Test target to run the program
test: $(TARGET)
	./$(TARGET) test_gps.txt output.txt

# Help target
help:
	@echo "Available targets:"
	@echo "  all     - Build the project (default)"
	@echo "  build   - Build the project"
	@echo "  check   - Check if build is successful"
	@echo "  clean   - Remove object files and executable"
	@echo "  test    - Run the program with test data"
	@echo "  help    - Show this help message"
