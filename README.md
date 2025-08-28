# GPS Path Planning Rover Project

## Understanding the Problem

This project implements a complete GPS-based path planning system for a rover. The system:
1. Decodes GPS data from u-blox GNSS module in UBX format
2. Converts GPS coordinates to grid positions
3. Plans optimal paths using a grid-based algorithm
4. Generates odometry commands for rover movement

## Thought Process and Implementation

### Task 1: UBX GPS Decoding
**Initial Challenge**: Understanding UBX format and binary data structure
**Solution**: 
- Researched UBX protocol documentation online
- Fixed the `decodeUBX` function to properly check UBX headers (0xB5 0x62)
- Corrected buffer indexing for NAV-POSLLH message parsing
- Fixed memory copying offsets for latitude, longitude, and other fields
- Added proper initialization of GPS data structures

**Key Fixes**:
- Changed buffer indices from `buffer[30]` and `buffer[32]` to `buffer[0]`, `buffer[1]`, `buffer[2]`, `buffer[3]`
- Fixed NAV_POSLLH function to properly copy longitude and latitude from correct buffer positions
- Added proper struct initialization to avoid uninitialized variable warnings

### Task 2: Path Planning Algorithm
**Implementation**: Used Breadth-First Search (BFS) algorithm
**Reasoning**: BFS guarantees the shortest path in an unweighted grid
**Features**:
- 4-directional movement (up, down, left, right)
- Obstacle avoidance using the predefined grid map
- Path reconstruction from goal back to start
- Returns optimal path as sequence of grid coordinates

### Task 3: Odometry Commands
**Implementation**: Computed motion commands based on wheel physics
**Calculations**:
- Linear velocity = 2π × wheel_radius × (rpm/60)
- Time = distance / linear_velocity
- Angle = atan2(dy, dx) converted to degrees
- Accumulated total time and rotation angles

### Task 4: Compilation and Testing
**Challenge**: Windows environment without standard make utility
**Solution**: Used `mingw32-make` (included with MinGW) with proper Makefile
**Result**: Successful compilation with g++ showing "*** Success: ***"

## Technical Details

### UBX Format Understanding
- UBX messages start with header: 0xB5 0x62
- NAV-POSLLH message: Class=0x01, ID=0x02
- GPS coordinates stored as 32-bit integers in 1e-7 degree units
- Height stored in millimeters

### Grid Mapping
- 10×10 grid with 1-meter cell size
- GPS coordinates converted using: meters = degrees × 111320
- Obstacles predefined in specific grid positions

### Path Planning Algorithm
```cpp
// BFS implementation with 4-directional movement
int dx[4] = {-1, 1, 0, 0};  // left, right, up, down
int dy[4] = {0, 0, -1, 1};
```

### Odometry Calculations
```cpp
// Wheel physics
linear_vel = 2 * M_PI * radius * (rpm / 60.0);
time_sec = distance / linear_vel;
angle_deg = atan2(y2-y1, x2-x1) * 180.0 / M_PI;
```

## Resources Used

1. **Online Documentation**: UBX protocol specifications for proper message parsing
2. **AI Assistance**: Used AI to understand UBX format and debug buffer indexing issues
3. **Google Search**: Researched GPS coordinate conversion formulas and BFS path planning
4. **Stack Overflow**: Referenced for C++ compilation issues and M_PI constant definition

## Challenges Faced

1. **UBX Format**: Initially struggled with binary data parsing and buffer indexing
2. **Windows Environment**: Had to create alternative to make commands
3. **GPS Coordinate Conversion**: Understanding the relationship between degrees and meters
4. **Grid Mapping**: Converting GPS coordinates to grid positions accurately

## Build Instructions

### Using Makefile (Recommended)
```bash
# Build the project
mingw32-make build

# Check if build is successful
mingw32-make check

# Clean build files
mingw32-make clean

# Run with test data
mingw32-make test

# Show help
mingw32-make help
```

### Direct Compilation
```bash
g++ -std=c++17 -Wall -Wextra -O2 main.cpp ublox_reader.cpp planning.cpp odometry.cpp gridmap.cpp -o rover
```

## Testing Results

- ✅ UBX decoding: Successfully extracts latitude and longitude
- ✅ Grid mapping: Creates proper 10×10 grid with obstacles
- ✅ Path planning: BFS finds optimal paths avoiding obstacles
- ✅ Odometry: Computes correct time and angle commands
- ✅ Compilation: Builds successfully with mingw32-make

## Files Modified

1. **ublox_reader.cpp**: Fixed UBX decoding logic and buffer indexing
2. **planning.cpp**: Implemented BFS path planning algorithm
3. **odometry.cpp**: Implemented motion command calculations
4. **main.cpp**: Added M_PI definition for Windows compatibility
5. **Makefile**: Created comprehensive build system for MinGW
6. **README.md**: This comprehensive documentation

## Conclusion

All four tasks have been successfully completed. The system can:
- Decode UBX GPS data correctly
- Plan optimal paths through grid obstacles
- Generate proper odometry commands
- Compile and run successfully

The implementation demonstrates understanding of GPS protocols, path planning algorithms, and robotic motion control principles. 

