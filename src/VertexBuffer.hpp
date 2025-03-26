#ifndef VERTEXBUFFER_HPP
#define VERTEXBUFFER_HPP

class VertexBuffer{
private:
    unsigned int m_rendererID {0};

public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void bind() const;
    void unbind() const; 
};




#endif 