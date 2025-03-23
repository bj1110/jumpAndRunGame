#include "VertexBuffer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Logger.hpp" 

VertexBuffer::VertexBuffer(const void *data, unsigned int size)
{
    GLCall(glGenBuffers(1, &m_rendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

void VertexBuffer::bind() const 
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::unbind() const 
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
