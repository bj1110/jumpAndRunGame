#include "VertexArray.hpp"
#include "Logger.hpp"


VertexArray::VertexArray()
{
    // std::cout << "Constructor VertexArray called" <<std::endl; 
    GLCall(glGenVertexArrays(1, &m_rendererID));
    GLCall(glBindVertexArray(m_rendererID));
}

VertexArray::~VertexArray()
{
    // std::cout << "Destructor VertexArray called" <<std::endl; 
    GLCall(glDeleteVertexArrays(1, &m_rendererID));
}

void VertexArray::AddBuffer(const VertexBuffer &vb, const VertexBufferLayout &layout)
{
    bind();
    vb.bind();
    const auto& elements= layout.getElements();
    unsigned int offset=0; 
    for(unsigned int i=0; i<elements.size(); i++){
        const auto& element= elements[i];
        GLCall(glEnableVertexAttribArray(i));
        // std::cout << "Element["<<i<<"]:"<<element.count<< " "<<element.type<<" size: "<< VertexBufferElement::GetSizeOfType(element.type)<<" "<< element.normalized<<std::endl; 
        // std::cout<< offset <<":"<< reinterpret_cast<void*>(offset) << std::endl; 
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), reinterpret_cast<void*>(offset)));   
        offset+= element.count * VertexBufferElement::GetSizeOfType(element.type); 
    }

}

void VertexArray::bind() const
{
    glBindVertexArray(m_rendererID);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}
