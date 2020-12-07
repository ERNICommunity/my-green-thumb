# Tests

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Create CMake project
set(PROJECT "my-green-thumb")
project(${PROJECT} VERSION 1.0.0 LANGUAGES CXX)

# Set Language Standards
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set names of needed components
set(TARGET "${PROJECT}_tests")
set(LIBRARY_CORE "${PROJECT}_lib-core")

# Includes
include(CTest)
enable_testing()

# Add libraries
add_subdirectory(googletest)
add_subdirectory("../core" ${CMAKE_CURRENT_BINARY_DIR}/src)

# Sources
set(SOURCES 
    "Test_TaskTimer.cpp"
    "main.cpp"
)
set(COMPILER_FLAGS "-O0;-g")

# Add and configure target
add_executable(${PROJECT} ${SOURCES})
target_link_libraries(${PROJECT} PRIVATE 
    ${LIBRARY_CORE} 
    gtest
    gmock
    pthread
)
target_compile_options(${PROJECT} PUBLIC ${COMPILER_FLAGS})

add_test(NAME ${LIBRARY_CORE}.${PROJECT} COMMAND ${PROJECT})