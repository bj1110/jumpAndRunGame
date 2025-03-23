#include "logger.hpp"

const std::unordered_map<GLenum, std::string> Logger::errorNames{
    { GL_NO_ERROR, "GL_NO_ERROR" },
    { GL_INVALID_ENUM, "GL_INVALID_ENUM" },
    { GL_INVALID_VALUE, "GL_INVALID_VALUE" },
    { GL_INVALID_OPERATION, "GL_INVALID_OPERATION" },
    { GL_STACK_OVERFLOW, "GL_STACK_OVERFLOW" },
    { GL_STACK_UNDERFLOW, "GL_STACK_UNDERFLOW" },
    { GL_OUT_OF_MEMORY, "GL_OUT_OF_MEMORY" },
    { GL_INVALID_FRAMEBUFFER_OPERATION, "GL_INVALID_FRAMEBUFFER_OPERATION" }
};

bool Logger::GLCheckError(const std::source_location location) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << lookUpErrorCode(error)
                    << ") in: " << location.function_name() << ": " << location.line() << std::endl;
        return false;
    }
    return true;
}

void Logger::GLClearError() {
    while (glGetError() != GL_NO_ERROR);
}

std::string Logger::lookUpErrorCode(GLenum error) {
    if (errorNames.contains(error)) {
        return ": " + errorNames.at(error);
    }
    return "";
}

