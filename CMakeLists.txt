cmake_minimum_required(VERSION 3.28)  # Ensure C++20 module support
project(OpenGLWSL)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find OpenGL and dependencies
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Enable C++20 modules
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -fmodules-ts")

# Add the module as a library
add_library(logger_module STATIC)
target_sources(logger_module PRIVATE src/logger.ixx)
target_compile_features(logger_module PUBLIC cxx_std_20)

# Main executable
add_executable(OpenGLWSL src/main.cpp)

# Link dependencies
target_link_libraries(OpenGLWSL OpenGL::GL ${GLEW_LIBRARIES} glfw logger_module)