#include <Shader.hpp>
#include <fstream>
#include <sstream>

Shader::Shader(const std::string& sourcepath): m_sourcepath(sourcepath)
{
    std::string shaderPath = std::string(PROJECT_SOURCE_DIR) + "/res/shaders/basic.shader";
    auto [vertexShader, fragmentShader] = parseShader(shaderPath);
    m_rendererID = CreateShader(vertexShader, fragmentShader);
    GLCall(glUseProgram(m_rendererID));
}
Shader::~Shader(){
    GLCall(glDeleteProgram(m_rendererID));
}
void Shader::bind() const{
    GLCall(glUseProgram(m_rendererID));
}
void Shader::unbind() const {
    GLCall(glUseProgram(0));
}
unsigned int Shader::getID() const {
    return m_rendererID; 
}

void Shader::updateUniform4f(const std::string &name, float v1, float v2, float v3, float v4)
{
    int location= getUniformLocation(name);
    GLCall(glUniform4f(location, v1, v2, v3, v4));
    bind(); 
}

int Shader::getUniformLocation(const std::string &name)
{
    if(m_UniformsCache.contains(name)){
        return m_UniformsCache[name];
    }
    GLCall(int location = glGetUniformLocation(m_rendererID, "u_Color"));
    if(location == -1){
        std::cerr << "uniform not found "<<std::endl; 
    }
    m_UniformsCache.insert({name, location}); 
    return location; 
}

unsigned int Shader::CreateShader(const std::string &vertexShader, const std::string &fragmentShader) const
{
    unsigned int programm = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    
    glAttachShader(programm, vs);
    glAttachShader(programm, fs);
    glLinkProgram(programm);
    glValidateProgram(programm);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return programm;
}

ShaderProgrammSource Shader::parseShader(const std::string& filepath) const{
    std::fstream file(filepath);
    
    enum class ShaderType{
        NONE= -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2]; 
    ShaderType type = ShaderType::NONE;
    while(std::getline(file, line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos){
                type= ShaderType::VERTEX;

            } else if(line.find("fragment") != std::string::npos){
                type= ShaderType::FRAGMENT;
            }
        }
        else{
            ss[(int) type] << line << "\n";
        }
    }
    return {ss[0].str(), ss[1].str()};
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source) const{
    unsigned int id= glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*) alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile "<<(type == GL_VERTEX_SHADER ? "vertex": "fragment") << " shader " <<std::endl; 
        std::cout << message <<std::endl; 
        glDeleteShader(id);
        return 0; 
    }
    return id; 
}
