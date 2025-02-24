cmake_minimum_required(VERSION 3.3)

project(csv-parser)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the compiler
set(CMAKE_C_COMPILER /opt/homebrew/Cellar/llvm/19.1.7/bin/clang)
set(CMAKE_CXX_COMPILER /opt/homebrew/Cellar/llvm/19.1.7/bin/clang++)

# Add C++14 flag
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")


# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    src/main.cpp
    src/CSVParserStage1.h
    src/CSVParserStage2.h
    src/CSVParserStage3.h
)

# Add executable
add_executable(csv-parser ${SOURCES})

# Link libraries (if any)
# target_link_libraries(csv-parser <library_name>)