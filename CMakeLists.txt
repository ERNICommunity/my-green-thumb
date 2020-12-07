cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(PROJECT "my-green-thumb-dummy")
project(${PROJECT} VERSION 1.0.0)

# Set Language Standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add projects
add_subdirectory("app")
#add_subdirectory("tests")