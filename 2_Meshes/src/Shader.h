#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader{
private:
    // the program ID
    unsigned int ID;

    std::string readShader(const char *filePath);

public:
    // constructor reads and builds the shader
    Shader(){}
    Shader(const char* vertexShaderPath, const char* fragmentShaderPath);
    // use/activate the shader
    void use() const;
    unsigned int getID() const;
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setMat4(const std::string &name, float matrix[]) const;
    void setVec3(const std::string &name, float vec3[]) const;
    void setVec3(const std::string &name, glm::vec3 vec3) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
};

#endif