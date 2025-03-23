cmake_policy(SET CMP0072 NEW)
set(OpenGL_GL_PREFERENCE "GLVND")

cmake_minimum_required(VERSION 3.28)
project(OpenGLWSL)

set(CMAKE_CXX_STANDARD 20)

# OpenGL & GLFW suchen
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Executable erstellen
# add_executable(OpenGLWSL src/main.cpp)

add_executable(OpenGLWSL src/main.cpp src/Logger.cpp src/VertexBuffer.cpp src/IndexBuffer.cpp  src/VertexArray.cpp )
target_include_directories(OpenGLWSL PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Include Directories für GLEW & GLFW setzen
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${glfw3_INCLUDE_DIRS})

# Richtige Bibliotheken linken
target_link_libraries(OpenGLWSL OpenGL::GL ${GLEW_LIBRARIES} glfw)

target_compile_definitions(OpenGLWSL PRIVATE PROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")