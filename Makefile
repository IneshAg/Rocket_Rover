CXX = g++
CXXFLAGS = -std=c++17 -Og -g -Wall

# default target
all: main

# build main executable
main: src/main.cpp src/ublox_reader.cpp src/planning.cpp src/odometry.cpp src/gridmap.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp src/ublox_reader.cpp src/planning.cpp src/odometry.cpp src/gridmap.cpp -Ilib -lm -o main

check: main
	@echo "--------------------------------------------"
	@echo "Checking..."
	@echo "Test-1: "
	./main test/testcase1.txt test/result1.txt
	@echo "Test-2: "
	./main test/testcase2.txt test/result2.txt
	@echo "Test-3: "
	./main test/testcase3.txt test/result3.txt
	@echo "**** Success: ***"
	@echo "--------------------------------------------"

clean:
	rm -f main test/result*

.PHONY: all clean check
