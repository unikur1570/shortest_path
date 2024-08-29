cmake_minimum_required(VERSION 3.14)
project(AStar)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_SOURCE_DIR}/include)

include(FetchContent)
FetchContent_Declare(
    argparse
    GIT_REPOSITORY https://github.com/p-ranav/argparse.git
    GIT_TAG        v3.1
)
FetchContent_MakeAvailable(argparse)

# Argparse
option(ARGPARSE_SHARED "Build shared library" OFF)
option(ARGPARSE_STATIC "Build static library" ON)

add_executable(shortest_path src/main.cpp)
target_link_libraries(shortest_path argparse)

