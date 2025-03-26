#ifndef VERTEXARRAY_HPP
#define VERTEXARRAY_HPP

#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArray{
private:
    unsigned int m_rendererID {0};

public:
    VertexArray();
    ~VertexArray(); 

    void AddBuffer (const VertexBuffer& vb, const VertexBufferLayout& layout);
    void bind() const;
    void unbind() const; 
};




#endif 