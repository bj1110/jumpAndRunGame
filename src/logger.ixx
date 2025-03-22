export module logger;

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>
#include <unordered_map>
#include <source_location>


export namespace GL_Logger{
    export class logger{

    public:
        template<typename Func, typename ... Args>
        static auto GLLog(Func&& func, Args&&... args, const std::source_location location= std::source_location::current()) -> decltype(func(args...)){
            GLClearError();
            auto result = func(std::forward<Args>(args)...);
            GLCheckError(location); 
            return result; 
        }


    private:

        static bool GLCheckError(const std::source_location location){
            while (GLenum error = glGetError()){
                std::cout <<"[OpenGL Error] ("<< error << lookUpErrorCode(error) << " in: " << location.function_name() <<": "<<location.line() <<std::endl; 
                return false;
            }
            return true;
        }

        static void GLClearError(){
            while(glGetError() != GL_NO_ERROR);
        }

        static std::string lookUpErrorCode(GLenum error){
            if(errorNames.contains(error)){
                return ": " + errorNames.at(error);
            }
            return "";
        }


        static const std::unordered_map<GLenum, std::string> errorNames;
    };

    const std::unordered_map<GLenum, std::string> logger::errorNames{
        { GL_NO_ERROR, "GL_NO_ERROR" },
        { GL_INVALID_ENUM, "GL_INVALID_ENUM" },
        { GL_INVALID_VALUE, "GL_INVALID_VALUE" },
        { GL_INVALID_OPERATION, "GL_INVALID_OPERATION" },
        { GL_STACK_OVERFLOW, "GL_STACK_OVERFLOW" },
        { GL_STACK_UNDERFLOW, "GL_STACK_UNDERFLOW" },
        { GL_OUT_OF_MEMORY, "GL_OUT_OF_MEMORY" },
        { GL_INVALID_FRAMEBUFFER_OPERATION, "GL_INVALID_FRAMEBUFFER_OPERATION" }
    };

}