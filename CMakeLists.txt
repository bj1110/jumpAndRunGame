cmake_minimum_required(VERSION 3.10)
project(OpenGLWSL)

set(CMAKE_CXX_STANDARD 17)
find_package(OpenGL REQUIRED)

add_executable(OpenGLWSL main.cpp)
target_link_libraries(OpenGLWSL OpenGL::GL glfw GLEW)

cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(OpenGL REQUIRED)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
target_link_libraries(OpenGLWSL ${GLEW_LIBRARIES})