#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <source_location>

namespace GL_Logger {
    class Logger {
    public:
        template<typename Func, typename ... Args>
        static auto GLLog(Func&& func, Args&&... args, const std::source_location location = std::source_location::current()) 
            -> decltype(func(args...)) {
            GLClearError();
            auto result = func(std::forward<Args>(args)...);
            GLCheckError(location);
            return result;
        }

    private:
        static bool GLCheckError(const std::source_location location);
        static void GLClearError();
        static std::string lookUpErrorCode(GLenum error);

        static const std::unordered_map<GLenum, std::string> errorNames;
    };
}

#endif // LOGGER_HPP
