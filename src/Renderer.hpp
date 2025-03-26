#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "VertexArray.hpp"
#include "Logger.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

class Renderer{
private:
    // int m_rendererID;
    // VertexArray& m_va;
    // IndexBuffer& m_ib; 
    // Shader& m_shader;
    // VertexBuffer& m_vb;

public: 
    void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

    void clear() const;

};








#endif