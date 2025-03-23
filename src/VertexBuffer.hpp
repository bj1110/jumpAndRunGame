#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

class VertexBuffer{
private:
    unsigned int m_rendererID;

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind();
    void unbind(); 
};




#endif 