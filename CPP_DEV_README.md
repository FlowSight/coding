# C++ Development Environment Configuration

## Directory Structure
- `build/` - Build artifacts and temporary files
- `executables/` - Compiled executables
- Source files organized by topic (array/, dp/, graph/, etc.)

## Compilation Standards
- C++17 standard
- Wall and Wextra warnings enabled
- O2 optimization
- pthread support for multithreading

## Usage Examples

### Quick Shortcuts (Recommended):
```bash
# Fastest way - Just run a file
./run multithreading/basic.cpp

# Short Makefile alias
make r FILE=multithreading/basic.cpp
```

### Using the build script:
```bash
# Compile and run a file
./tools/build/build_and_run.sh multithreading/basic.cpp

# Compile with custom name
./tools/build/build_and_run.sh multithreading/basic.cpp my_threading_app
```

### Using Makefile:
```bash
# Compile a file
make compile FILE=multithreading/basic.cpp

# Compile and run (full command)
make run FILE=multithreading/basic.cpp

# Compile and run (short alias)
make r FILE=multithreading/basic.cpp

# Clean build artifacts
make clean

# Show help
make help
```

### Manual compilation:
```bash
# Basic compilation
g++ -std=c++17 -Wall -Wextra -O2 -pthread multithreading/basic.cpp -o executables/basic

# Run the executable
./executables/basic
```

## Common Issues on macOS
- Use individual headers instead of `#include <bits/stdc++.h>`
- Always include `-pthread` flag for threading
- Use `-std=c++17` or newer for modern C++ features

## Recommended Headers for Common Tasks
```cpp
#include <iostream>     // Input/output
#include <vector>       // Dynamic arrays
#include <string>       // String operations
#include <algorithm>    // STL algorithms
#include <thread>       // Threading
#include <mutex>        // Thread synchronization
#include <memory>       // Smart pointers
#include <chrono>       // Time utilities
```