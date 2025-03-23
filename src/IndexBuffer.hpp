#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

class IndexBuffer{
private:
    unsigned int m_rendererID;
    unsigned int m_count; 

public:
    IndexBuffer(const unsigned int* data, unsigned int size);
    ~IndexBuffer();

    void bind() const ;
    void unbind() const; 
    inline unsigned int getCount() const ;
};




#endif 