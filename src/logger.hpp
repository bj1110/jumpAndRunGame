#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <source_location>

#define GLCall(x) Logger::GLClearError();\
    x;\
    Logger::GLCheckError()


class Logger {
    public:
        static bool GLCheckError(const std::source_location location= std::source_location::current()); 
        static void GLClearError();
        
    private:
        static std::string lookUpErrorCode(GLenum error);
        static const std::unordered_map<GLenum, std::string> errorNames;
};

#endif 
