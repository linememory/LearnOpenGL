#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

class Shader{
private:
    // the program ID
    unsigned int ID;

    std::string readShader(const char *filePath);

public:
    // constructor reads and builds the shader
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    // use/activate the shader
    void use();
    unsigned int getID() const;
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
};

#endif