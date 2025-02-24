cmake_minimum_required(VERSION 3.3)

project(csv-parser)

# Set the C and C++ compilers
set(CMAKE_C_COMPILER /opt/homebrew/bin/gcc-14)
set(CMAKE_CXX_COMPILER /opt/homebrew/bin/g++-14)

# Set the module path
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/Modules)

# OpenMP flags
set(OPENMP_CXX_FLAGS "-O3 -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPENMP_CXX_FLAGS}")

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source files
set(SOURCES
    csv-parser-project/src/main.cpp
    csv-parser-project/src/CSVParser.h
    csv-parser-project/src/CSVParserStage1.h
    csv-parser-project/src/CSVParserStage2.h
    csv-parser-project/src/RawRecord.h 

)

# Add executable
add_executable(csv-parser ${SOURCES})

# Link libraries (if any)
# target_link_libraries(csv-parser <library_name>)


