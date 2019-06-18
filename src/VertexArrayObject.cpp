#include "VertexArrayObject.h"
#include <iostream>


VertexArrayObject::VertexArrayObject(){
    glGenVertexArrays(1, &m_VAO);
    vertices_count = 0;
}

VertexArrayObject::~VertexArrayObject(){
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_EBO);
}

//VertexArrayObject::VertexArrayObject(float vertices[]);
//VertexArrayObject::VertexArrayObject(float vertices[], unsigned int indices[]);
void VertexArrayObject::setVertexData(float vertices[], int size){
    std::cout << m_VAO << ": " << size << std::endl;
    vertices_count = size;
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);
    glBindVertexArray(0);
}

void VertexArrayObject::setVertexAttribPointer(int index, int size, int offset, int stride, bool normalized){
    glBindVertexArray(m_VAO);
    glVertexAttribPointer(index, size, GL_FLOAT, normalized, stride * sizeof(float), (void*)(offset*sizeof(float)));
    glEnableVertexAttribArray(index);
    glBindVertexArray(0);
}

void VertexArrayObject::setIndices(unsigned int indices[], int size){
    std::cout << m_VAO << ": " << size << std::endl;
    vertices_count = size;
    glGenBuffers(1, &m_EBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(int), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
    std::cout << m_EBO << std::endl;
}

void VertexArrayObject::setShaderProgram(Shader shaderProgram){
    m_ShaderProgram = shaderProgram;
}

void VertexArrayObject::draw() {
    glBindVertexArray(m_VAO);
    m_ShaderProgram.use();
    if (m_EBO == 0){
        glDrawArrays(GL_TRIANGLES, 0, vertices_count);
    }
    else{
        glDrawElements(GL_TRIANGLES, vertices_count, GL_UNSIGNED_INT, (void*)0);
   }
}