cmake_minimum_required(VERSION 3.10)
project(CompressionTool)

set(CMAKE_CXX_STANDARD 11)

# Specify the source files
set(SOURCES 
    src/main.cpp
    src/huffman.cpp
    src/utils.cpp
)

# Specify the header files directory
include_directories(include)

# Create executable
add_executable(compression_tool ${SOURCES})

# Copy input files to build directory
file(COPY input DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

