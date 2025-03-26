#ifndef INDEXBUFFER_HPP
#define INDEXBUFFER_HPP

class IndexBuffer{
private:
    unsigned int m_rendererID{0};
    unsigned int m_count{0}; 

public:
    IndexBuffer(const unsigned int* data, unsigned int size);
    ~IndexBuffer();

    void bind() const ;
    void unbind() const; 
    inline unsigned int getCount() const{
        return m_count; 
    }
};




#endif 