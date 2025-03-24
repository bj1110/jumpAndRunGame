#include "IndexBuffer.hpp"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cassert>

#include "Logger.hpp" 

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : m_count(count)
{
    // std::cout << "IndexBuffer Constructor called" <<std::endl; 
    assert(sizeof(unsigned int ) == sizeof(GLuint) && "unsigned int != GLuint"); 
    GLCall(glGenBuffers(1, &m_rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
    // std::cout << "IndexBuffer Destructor called" <<std::endl; 
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

void IndexBuffer::bind() const 
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void IndexBuffer::unbind() const 
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

inline unsigned int IndexBuffer::getCount() const 
{
    return m_count;
}
