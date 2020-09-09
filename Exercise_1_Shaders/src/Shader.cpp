#include "../include/Shader.h"

void Shader::ShaderParser(const char *path){

    enum class ShaderType{
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    std::fstream source;
    source.open(path, std::fstream::in);
    if(!source.is_open()){
        std::cout << "Failed to open the file." << path << std::endl;
    }
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;
    while(std::getline(source, line)){
        if(line.find("#shader") != std::string::npos){
            if(line.find("vertex") != std::string::npos){
                type = ShaderType::VERTEX;
            } else if(line.find("fragment") != std::string::npos){
                type = ShaderType::FRAGMENT;
            }
        }
        else{
            ss[(unsigned int)type] << line << "\n";
        }
    }
    ShaderProgramSource.vertexSource = ss[0].str();
    ShaderProgramSource.fragmentSource = ss[1].str();
}

unsigned int Shader::CreateShader(){

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, ShaderProgramSource.vertexSource);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, ShaderProgramSource.fragmentSource);

    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

unsigned int Shader::CompileShader(unsigned int type, const std::string &source){

    unsigned int id = glCreateShader(type);

    const char* src = source.c_str();
    glShaderSource(id, 1, &src, NULL);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if(!result){
        char log[512];
        glGetShaderInfoLog(id, 512, NULL, log);
        std::cout << "ERROR::SHADER::" <<  ((type == GL_FRAGMENT_SHADER) ? "FRAGMENT" : "VERTEX")  <<
            "::COMPILATION_FAILED\n" << log <<std::endl;
        return 0;
    }
    return id;

}
