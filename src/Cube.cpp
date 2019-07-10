#include "Cube.h"
#include "stb_image.h"


unsigned int TextureFromFile(const char *path);

Cube::Cube(glm::vec3 position, glm::vec3 size, glm::vec3 rotation) :
    Model(position, size, glm::quat(rotation)){

}

void Cube::createCube(std::string diffuseTexture, std::string specularTexture){
    std::vector<Vertex> vertices{
        // front
        {{-0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f},},
        {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},},
        {{ 0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f},},
        {{-0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f},},
        {{ 0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f},},
        {{ 0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f},},
        // back
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f},},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f},},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f},},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f},},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f},},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f},},
        // left
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
        {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f},},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
        {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
        {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
        {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f},},
        // right
        {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
        {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f},},
        {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
        {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
        {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
        {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f},},
        // top
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
        {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f},},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
        {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
        {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
        {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f},},
        // bottom
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
        {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f},},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
        {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
        {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
        {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f},},
    };

    std::vector<Texture> textures;
    // if(specularTexture.size() == 0)
    //     specularTexture = diffuseTexture;
    textures.push_back(loadTexture(diffuseTexture, TextureType::DIFFUSE));
    if(specularTexture.size() != 0)
        textures.push_back(loadTexture(specularTexture, TextureType::SPECULAR));
    m_meshes.push_back(Mesh(vertices, std::vector<unsigned int>(), textures));
}


Texture Cube::loadTexture(std::string path, TextureType type){
    Texture texture;
    texture.id = TextureFromFile(path.c_str());
    texture.type = type;
    texture.path = path;
    return texture;
}

unsigned int TextureFromFile(const char *path){
    unsigned int ID = 0;
	glGenTextures(1, &ID);
	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if(data){
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;
		glBindTexture(GL_TEXTURE_2D, ID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	} else {
		std::cerr << "Failed to load texture at path: " << path << std::endl;
	}
	stbi_image_free(data);
	return ID;
}


// unsigned int TextureFromFile(const char *path);

// Cube::Cube(glm::vec3 position, glm::vec3 size, glm::vec3 rotation) : 
//     m_position{position}, 
//     m_size{size}, 
//     m_rotation{rotation}, 
//     m_shader{Shader{"data/shader/cube.vs", "data/shader/cube.fs"}},
//     m_outlineShader{"data/shader/outline.vs", "data/shader/outline.fs"},
//     m_outline{false}{
//         createCube();
// }

// void Cube::loadTexture(std::string path, TextureType type){
//     Texture texture;
//     texture.id = TextureFromFile(path.c_str());
//     texture.type = type;
//     texture.path = path;
//     m_textures.push_back(texture);
// }

// void Cube::setShader(std::string vertexShaderPath, std::string fragmentShaderPath){
//     m_shader = Shader{vertexShaderPath.c_str(), fragmentShaderPath.c_str()};
// }

// void Cube::drawOutline(bool outline){
//     m_outline = outline;
// }

// void Cube::createMesh(){
//     m_meshCreated = true;
//     m_mesh = Mesh(m_vertices, std::vector<unsigned int>(), m_textures);
// }

// void Cube::draw(glm::mat4 view, glm::mat4 projection){
//     if (!m_meshCreated)
//         createMesh();
//     glm::mat4 model = glm::mat4(1.0f);
//     model = glm::translate(model, m_position);
//     model = glm::scale(model, m_size);

//     glClear(GL_STENCIL_BUFFER_BIT);
//     glEnable(GL_STENCIL_TEST);
//     glStencilFunc(GL_ALWAYS, 1, 0xFF);
//     glStencilMask(0xFF);
//     glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

//     m_shader.use();
//     m_shader.setMat4("model", glm::value_ptr(model));
//     m_shader.setMat4("view", glm::value_ptr(view));
//     m_shader.setMat4("projection", glm::value_ptr(projection));
//     m_mesh.draw(m_shader);

//     if(m_outline){
//         glStencilFunc(GL_EQUAL, 0, 0xFF);
//         glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
//         glStencilMask(0x00);
//         //glDisable(GL_DEPTH_TEST);

//         model = glm::scale(model, m_size+0.05f);
//         m_outlineShader.use();
//         m_outlineShader.setMat4("model", glm::value_ptr(model));
//         m_outlineShader.setMat4("view", glm::value_ptr(view));
//         m_outlineShader.setMat4("projection", glm::value_ptr(projection));
//         m_mesh.draw(m_outlineShader);

//         glStencilMask(0xFF);
//         glBindVertexArray(0);
//         //glEnable(GL_DEPTH_TEST);
//     }
// }

// void Cube::createCube(){
//     m_vertices = {
//         // front
//         {{-0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f},},
//         {{-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f},},
//         {{ 0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f},},
//         {{-0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f},},
//         {{ 0.5f, -0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f},},
//         {{ 0.5f,  0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f},},
//         // back
//         {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f},},
//         {{ 0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f},},
//         {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f},},
//         {{ 0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f},},
//         {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f},},
//         {{-0.5f,  0.5f, -0.5f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f},},
//         // left
//         {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
//         {{-0.5f, -0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f},},
//         {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
//         {{-0.5f,  0.5f,  0.5f}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
//         {{-0.5f, -0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
//         {{-0.5f,  0.5f, -0.5f}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f},},
//         // right
//         {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
//         {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f},},
//         {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
//         {{0.5f,  0.5f, -0.5f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f},},
//         {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f},},
//         {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f},},
//         // top
//         {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
//         {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f},},
//         {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
//         {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
//         {{ 0.5f,  0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
//         {{ 0.5f,  0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f},},
//         // bottom
//         {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
//         {{-0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f},},
//         {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
//         {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f},},
//         {{ 0.5f, -0.5f,  0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f},},
//         {{ 0.5f, -0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f},},
//     };
// }

// unsigned int TextureFromFile(const char *path){
//     unsigned int ID = 0;
// 	glGenTextures(1, &ID);
// 	int width, height, nrComponents;
// 	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
// 	if(data){
// 		GLenum format;
// 		if (nrComponents == 1)
// 			format = GL_RED;
// 		else if (nrComponents == 3)
// 			format = GL_RGB;
// 		else if (nrComponents == 4)
// 			format = GL_RGBA;
// 		glBindTexture(GL_TEXTURE_2D, ID);
// 		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
// 		glGenerateMipmap(GL_TEXTURE_2D);

// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
// 		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// 	} else {
// 		std::cerr << "Failed to load texture at path: " << path << std::endl;
// 	}
// 	stbi_image_free(data);
// 	return ID;
// }