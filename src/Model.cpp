#include "Model.h"


Model::Model(glm::vec3 position, glm::vec3 size, glm::quat rotation) :
    transform{position, size, rotation}{

}

void Model::setMeshes(std::vector<Mesh> meshes){
    m_meshes = meshes;
}

void Model::addMesh(Mesh mesh){
    m_meshes.push_back(mesh);
}

void Model::setShader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath){
    m_shader = Shader{vertexShaderPath.c_str(), fragmentShaderPath.c_str()};
}

void Model::draw(const glm::mat4 &view, const glm::mat4 &projection){
    glm::mat4 model = glm::mat4(1.0f);
    for (Mesh mesh : m_meshes){
        model = glm::mat4(1.0f);
        model = glm::translate(model, transform.position);
        model = glm::scale(model, transform.size);

        glClear(GL_STENCIL_BUFFER_BIT);
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        m_shader.use();
        m_shader.setMat4("model", glm::value_ptr(model));
        m_shader.setMat4("view", glm::value_ptr(view));
        m_shader.setMat4("projection", glm::value_ptr(projection));
        mesh.draw(m_shader);

        if(m_outline){
            glStencilFunc(GL_EQUAL, 0, 0xFF);
            glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
            glStencilMask(0x00);
            //glDisable(GL_DEPTH_TEST);

            model = glm::scale(model, transform.size+0.05f);
            m_outlineShader.use();
            m_outlineShader.setMat4("model", glm::value_ptr(model));
            m_outlineShader.setMat4("view", glm::value_ptr(view));
            m_outlineShader.setMat4("projection", glm::value_ptr(projection));
            mesh.draw(m_outlineShader);

            glStencilMask(0xFF);
            glBindVertexArray(0);
            //glEnable(GL_DEPTH_TEST);
        }
    }
}

void Model::drawOutline(bool outline){
    m_outline = outline;
}


