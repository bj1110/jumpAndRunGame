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
#include "Renderer.hpp"


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

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

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

        float positions2[]={
            -0.9f, -0.9f,
            -0.3f, -0.9f,
            -0.3f, -0.3f,
            -0.9f, -0.3f
        };

        VertexArray va;
        VertexBuffer vb (positions, 4*2*sizeof(float));
        VertexBufferLayout layout;
        layout.push<float>(2, GL_FALSE);
        va.AddBuffer(vb, layout);        
        IndexBuffer ib(indices, 6);
        Renderer renderer; 
        
        std::string shaderPath="/res/shaders/basic.shader";
        Shader shader {shaderPath};
    
        float r = 0.1f;
        float dr= 0.01f; 
        shader.updateUniform4f("u_Color", r, 0.1f, 0.1f, 1.0f); 
        
        
        VertexArray va2;
        VertexBuffer vb2(positions2, 8* sizeof(float));
        va2.AddBuffer(vb2, layout); 
        
        
        while (!glfwWindowShouldClose(window)) {
            renderer.clear();
            if(r>=1 || r<=0){
                dr=-dr;
            } 
            r+=dr;
            shader.bind(); 
            shader.updateUniform4f("u_Color", r, 0.1f, 0.1f, 1.0f); 
            
            renderer.draw(va, ib, shader);
             
            shader.updateUniform4f("u_Color", 0.9f, 0.9f, 0.9f, 0.3f);

            renderer.draw(va2, ib, shader);


            glfwSwapBuffers(window);
            glfwPollEvents();

        } 
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}