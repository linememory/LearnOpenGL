#include "Shader.h"

Shader::Shader(const char* vertexShaderPath, const char* fragmentShaderPath){
    std::string vertexCode = readShader(vertexShaderPath);
    std::string fragmentCode = readShader(fragmentShaderPath);
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    // compile shaders
    unsigned int vertexShader, fragmentShader;
    int success;
	char infoLog[512];

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        std::cout << vShaderCode  << std::endl;
	}

	// fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	
	// link program
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::use() const{
    glUseProgram(ID);
}

unsigned int Shader::getID() const{
    return ID;
}

void Shader::setBool(const std::string &name, bool value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string &name, int value) const{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string &name, float value) const{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

std::string Shader::readShader(const char *filePath){
    std::stringstream ss;
    std::ifstream inFile;
    inFile.exceptions(std::fstream::failbit | std::fstream::badbit);
    try
    {
        inFile.open(filePath);
        ss << inFile.rdbuf();
        inFile.close();
    }
    catch(std::fstream::failure e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ: Filepath: " << filePath << "\n" << e.what() << '\n';
    }
    return ss.str();
}

