cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE "GLVND")

cmake_minimum_required(VERSION 3.10)
project(OpenGLWSL)

set(CMAKE_CXX_STANDARD 20)

# OpenGL & GLFW suchen
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Executable erstellen
add_executable(OpenGLWSL main.cpp)

# Include Directories für GLEW & GLFW setzen
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${glfw3_INCLUDE_DIRS})

# Richtige Bibliotheken linken
target_link_libraries(OpenGLWSL OpenGL::GL ${GLEW_LIBRARIES} glfw)
