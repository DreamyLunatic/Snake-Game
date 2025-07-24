# Minimum CMake version required
cmake_minimum_required(VERSION 3.15)

# Project name and version
project(Snake VERSION 1.0)

# Set C++ standard (e.g., C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files (adjust paths as needed)
file(GLOB SOURCES "src/*.cpp" "src/*.h")
add_executable(Snake ${SOURCES})

# Link libraries (e.g., SFML, OpenGL, etc.)
# Example for SFML:
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        5.0        # Use tag "5.0" for the latest stable release
    GIT_SHALLOW    TRUE
)
# Optional: Configure raylib build options (disable examples, enable shared lib, etc.)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)       # Don't build raylib examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)       # Don't build raylib games
# set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)   # Uncomm7ent to build as shared library

# Make raylib available in your project
FetchContent_MakeAvailable(raylib)

# Create your game executable
add_executable(Snake src/main.cpp)

# Link raylib to your executable
target_link_libraries(Snake PRIVATE raylib)

# Include directories (if needed)
target_include_directories(Snake PRIVATE include)