#ifndef VERTEXBUFFERLAYOUT_HPP
#define VERTEXBUFFERLAYOUT_HPP

#include <vector>
#include <GL/glew.h>
#include <iostream>


struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned int normalized;

    static unsigned int GetSizeOfType(unsigned int type){
        switch(type)
        {
            case GL_FLOAT: return 4;
            case GL_UNSIGNED_INT: return 4;
        }
        std::cerr<< "wrong type - no size found "<< std::endl; 
        return 0; 
    }
};


class VertexBufferLayout{
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_stride; 

public:
    VertexBufferLayout(){
        // std::cout<< "VertexBufferLayout Constructor called"<<std::endl;
        }
        ~VertexBufferLayout(){
        // std::cout<< "VertexBufferLayout Destructor called"<<std::endl;
        }

    template<typename T>
    inline void push(unsigned int count, unsigned int normalized);
    
    inline const std::vector<VertexBufferElement>& getElements() const{
        return m_Elements;
    }
    inline const unsigned int getStride() const{
        return m_stride; 
    }
};

template<typename T>
inline void VertexBufferLayout::push(unsigned int count, unsigned int normalized){
    // static_assert(false);
    std::cout << "chose wrong method "<< std::endl; 
}

template<>
inline void VertexBufferLayout::push<float>(unsigned int count, unsigned int normalized)
{
    m_Elements.push_back({GL_FLOAT, count, normalized});
    m_stride+= count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::push<unsigned int>(unsigned int count, unsigned int normalized)
{
    m_Elements.push_back({GL_UNSIGNED_INT, count, normalized}); 
    m_stride += count* VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
}



#endif 