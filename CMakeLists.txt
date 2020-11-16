cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(PROJECT "my-green-thumb")
project(${PROJECT} VERSION 1.0.0 LANGUAGES C CXX ASM)

# Set Language Standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Includes
include(${CMAKE_SOURCE_DIR}/cmake/utilities.cmake)  # Utilities for binary creation

# Disable common networking component, STM has it's own
set(DISABLE_COMMON_NETWORK true)

# Names
set(APP "${PROJECT}_exe")
set(LIBRARY_LIB "${PROJECT}_lib-core")
set(LIBRARY_CMSIS "${PROJECT}_lib-cmsis")
set(LIBRARY_HAL "${PROJECT}_lib-hal")

#Add externals
add_subdirectory("external")

# Add libraries
add_subdirectory("src")

# Add executable
add_subdirectory("app")
