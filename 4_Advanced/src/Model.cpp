#include "Model.h"


Model::Model(glm::vec3 position, glm::vec3 size, glm::quat rotation) :
    transform{position, size, rotation}, m_normalShader{"data/shader/normals.vs", "data/shader/normals.fs", "data/shader/normals.gs"}{
    
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

void Model::drawBoundingBox(glm::mat4 model, glm::mat4 view, glm::mat4 projection){
    std::vector<Vertex> verts;
    verts.push_back(Vertex{boundingBox.min}); // left bottom
    verts.push_back(Vertex{{boundingBox.max.x, boundingBox.min.y, boundingBox.min.z}}); // right bottom
    verts.push_back(Vertex{{boundingBox.min.x, boundingBox.max.y, boundingBox.min.z}});
    verts.push_back(Vertex{{boundingBox.max.x, boundingBox.max.y, boundingBox.min.z}});

    verts.push_back(Vertex{{boundingBox.min.x, boundingBox.min.y, boundingBox.max.z}});
    verts.push_back(Vertex{{boundingBox.max.x, boundingBox.min.y, boundingBox.max.z}});
    verts.push_back(Vertex{{boundingBox.min.x, boundingBox.max.y, boundingBox.max.z}});
    verts.push_back(Vertex{boundingBox.max});


    std::vector<unsigned int> indices{0,1,3, 0,3,2, 1,7,3, 1,5,7, 2,7,6, 2,3,7, 0,6,4, 0,2,6, 1,4,5, 1,0,4, 5,6,7, 5,4,6};
    m_boundingBox = Mesh{verts, indices}; 
    Shader shader{"data/shader/line.vs", "data/shader/line.fs"};
    shader.use();
    shader.setMat4("model", glm::value_ptr(model));
    shader.setMat4("view", glm::value_ptr(view));
    shader.setMat4("projection", glm::value_ptr(projection));
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    m_boundingBox.draw(shader);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Model::draw(const glm::mat4 &view, const glm::mat4 &projection){
    m_cullFace ? glEnable(GL_CULL_FACE) : glDisable(GL_CULL_FACE);
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
        //drawBoundingBox(model, view, projection);
        if(showNnormals){
            m_normalShader.use();
            m_normalShader.setMat4("model", glm::value_ptr(model));
            m_normalShader.setMat4("view", glm::value_ptr(view));
            m_normalShader.setMat4("projection", glm::value_ptr(projection));
            mesh.draw(m_normalShader);
        }
    }
}


