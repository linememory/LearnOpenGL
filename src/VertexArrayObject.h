#ifndef VERTEX_ARRAY_OBJECT_H
#define VERTEX_ARRAY_OBJECT_H

#include <glad/glad.h>
#include "Shader.h"

class VertexArrayObject {
private:
    unsigned int m_VAO, m_VBO, m_EBO = 0;
    Shader m_ShaderProgram;
    unsigned int vertices_count;
public:
    VertexArrayObject();
    //VertexArrayObject(float vertices[]);
    //VertexArrayObject(float vertices[], unsigned int indices[]);
    ~VertexArrayObject();

    void setVertexData(float vertices[], int size);
    void setIndices(unsigned int indices[], int size);
    void setVertexAttribPointer(int index, int size, int offset, int stride, bool normalized = false);
    void setShaderProgram(Shader shaderProgram);
    void draw();
};

#endif