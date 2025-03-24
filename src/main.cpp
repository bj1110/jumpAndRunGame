#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Logger.hpp" 
#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "Shader.hpp"


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
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
    {
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


        VertexArray va;
        VertexBuffer vb (positions, 4*2*sizeof(float));
        VertexBufferLayout layout;
        layout.push<float>(2, GL_FALSE);
        va.AddBuffer(vb, layout);        
        IndexBuffer ib(indices, 6);


        std::string shaderPath="/res/shaders/basic.shader";
        Shader shader {shaderPath};


        
        float r = 0.1f;
        float dr= 0.01f; 
        shader.updateUniform4f("u_Color", r, 0.1f, 0.1f, 1.0f); 
        
        
        while (!glfwWindowShouldClose(window)) {
            glClear(GL_COLOR_BUFFER_BIT);
            if(r>=1 || r<=0){
                dr=-dr;
            } 
            r+=dr;
            shader.updateUniform4f("u_Color", r, 0.1f, 0.1f, 1.0f); 
            va.bind();
            ib.bind(); 

            GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
            va.unbind();
            ib.unbind();

            glfwSwapBuffers(window);
            glfwPollEvents();

        } 
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}