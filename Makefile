CXX = g++
CXXFLAGS = -std=c++17 -Og -g -Wall

# default target
all: main

# build main executable
main: main.cpp ublox_reader.cpp planning.cpp odometry.cpp gridmap.cpp
	$(CXX) $(CXXFLAGS) main.cpp ublox_reader.cpp planning.cpp odometry.cpp gridmap.cpp -lm -o main

check: main
	@echo "--------------------------------------------"
	@echo "Checking..."
	@echo "Test-1: "
	./main test/testcase1.txt test/result1.txt
	fc test/result1.txt test/expected1.txt >nul 2>&1 || echo "Test 1 failed"
	@echo "Test-2: "
	./main test/testcase2.txt test/result2.txt
	fc test/result2.txt test/expected2.txt >nul 2>&1 || echo "Test 2 failed"
	@echo "Test-3: "
	./main test/testcase3.txt test/result3.txt
	fc test/result3.txt test/expected3.txt >nul 2>&1 || echo "Test 3 failed"
	@echo "**** Success: ***"
	@echo "--------------------------------------------"

clean:
	rm -f main test/result*

.PHONY: all clean check
