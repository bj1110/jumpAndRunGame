#ifndef SHADER_HPP
#define SHADER_HPP

#include "Logger.hpp"


struct ShaderProgrammSource{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader{
private:
    std::string m_sourcepath;
    unsigned int m_rendererID;
    std::unordered_map<std::string, int> m_UniformsCache;


public:
    Shader(const std::string& sourcepath);
    ~Shader();
    void bind() const;
    void unbind() const;
    unsigned int getID() const;
    void updateUniform4f(const std::string& name, float v1, float v2, float v3, float v4);

    
private: 
    int getUniformLocation(const std::string& name);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader) const;
    ShaderProgrammSource parseShader(const std::string& filepath) const ;
    unsigned int CompileShader(unsigned int type, const std::string& source) const;




};







#endif