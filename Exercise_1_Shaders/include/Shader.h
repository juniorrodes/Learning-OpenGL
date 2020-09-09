#pragma once

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

class Shader{

public:
    struct{
        std::string vertexSource;
        std::string fragmentSource;
    } ShaderProgramSource ;

    void ShaderParser(const char *path);
    unsigned int CreateShader();

private:
    unsigned int CompileShader(unsigned int type, const std::string &source);

};
