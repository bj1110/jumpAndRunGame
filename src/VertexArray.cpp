#include "VertexArray.hpp"
#include "Logger.hpp"


VertexArray::VertexArray()
{
    GLCall(glGenVertexArrays(1, &m_rendererID));
    GLCall(glBindVertexArray(m_rendererID));
}

VertexArray::~VertexArray()
{
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
        // TODO: nächste Zeile drawt gar nichts; übernächste nur 1 der 2 dreiecke
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), reinterpret_cast<void*>(offset)));  
        // glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), nullptr);  
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
