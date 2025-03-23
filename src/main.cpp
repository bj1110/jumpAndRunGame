#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Logger.hpp" 
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"


struct ShaderProgrammSource{
    std::string VertexSource;
    std::string FragmentSource;
};

static ShaderProgrammSource parseShader(const std::string& filepath){
    std::fstream file(filepath);
    
    enum class ShaderType{
        NONE= -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2]; 
    ShaderType type = ShaderType::NONE;
    while(std::getline(file, line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos){
                type= ShaderType::VERTEX;

            } else if(line.find("fragment") != std::string::npos){
                type= ShaderType::FRAGMENT;
            }
        }
        else{
            ss[(int) type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

static unsigned int CompileShader(unsigned int type, const std::string& source){
    unsigned int id= glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile "<<(type == GL_VERTEX_SHADER ? "vertex": "fragment") << " shader " <<std::endl; 
        std::cout << message <<std::endl; 
        glDeleteShader(id);
        return 0; 
    }
    return id; 
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
    unsigned int programm = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(programm, vs);
    glAttachShader(programm, fs);
    glLinkProgram(programm);
    glValidateProgram(programm);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return programm; 
}

int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW konnte nicht initialisiert werden!\n";
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL mit WSL", NULL, NULL);
    if (!window) {
        std::cerr << "Fenster konnte nicht erstellt werden!\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1); 

    if (glewInit() != GLEW_OK) {
        std::cerr << "GLEW konnte nicht initialisiert werden!\n";
        return -1;
    }

    // Bis hier ist alles initialisierung gewesen

    float positions[]={
        -0.5f, -0.5f, 
        -0.5f, 0.5f,
        0.5f, 0.5f,
        0.5f, -0.5f
    };

    unsigned int indices[]={
        0, 1, 2,
        2, 3, 0
    };


    VertexBuffer vb (positions, 4*2*sizeof(float));

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2* sizeof(float), 0); 
    glEnableVertexAttribArray(0);


    IndexBuffer ib(indices, 6);

    std::string shaderPath = std::string(PROJECT_SOURCE_DIR) + "/res/shaders/basic.shader";
    auto [vertexShader, fragmentShader] = parseShader(shaderPath);

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    int location = glGetUniformLocation(shader, "u_Color");
    if(location == -1){
        std::cerr << "uniform not found "<<std::endl; 
    }
    float r = 0.1f;
    float dr= 0.01f; 
    GLCall(glUniform4f(location, r, 0.1f, 0.1f, 1.0f)); 


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);
        if(r>=1 || r<=0){
            dr=-dr;
        } 
        r+=dr;
        GLCall(glUniform4f(location, r, 0.1f, 0.1f, 1.0f)); 
        // glDrawArrays(GL_TRIANGLES, 0, 3); 
        // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    glDeleteProgram(shader); 
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}