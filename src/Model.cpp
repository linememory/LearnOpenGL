#include "Model.h"
#include "stb_image.h"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

Model::Model(std::string const &path, bool gammaCorrection) : m_gammaCorrection{gammaCorrection}{
    loadModel(path);
}

void Model::draw(Shader shader){
    for(auto m : m_meshes){
        m.draw(shader);
    }
}

void Model::loadModel(std::string const &path){
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile(path, aiProcess_FlipUVs | aiProcess_Triangulate);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
        std::cerr << "ERROR::ASIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    m_directory = path.substr(0, path.find_last_of('/'));
    processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode const *node, const aiScene *scene){
   for (unsigned int i = 0; i < node->mNumMeshes; i++){
       aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
       m_meshes.push_back(processMesh(mesh, scene));
    }
    for (int i = 0; i < node->mNumChildren; i++){
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh const *mesh, const aiScene *scene){
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector;
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;
        if(mesh->mTextureCoords[0]){
            vertex.texCoords = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        } else {
            vertex.texCoords = glm::vec2(0.0f);
        }
        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    if(mesh->mMaterialIndex >= 0){
        aiMaterial const *material = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        std::vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }
    
    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::loadMaterialTextures(aiMaterial const *mat, aiTextureType type, std::string typeName){
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++){
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < m_textures_loaded.size(); j++)
        {
            if(std::strcmp(m_textures_loaded[j].path.c_str(), str.C_Str()) == 0){
                textures.push_back(m_textures_loaded[j]);
                skip = true;
                break;
            }
        }
        if(!skip){
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), m_directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            m_textures_loaded.push_back(texture);
        }
    }
    return textures;
}

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma){
    std::string filename = directory + "/" + path;
    unsigned int ID = 0;
	glGenTextures(1, &ID);
	int width, height, nrComponents;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
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
		std::cerr << "Failed to load texture at path: " << filename.c_str() << std::endl;
	}
	stbi_image_free(data);
	return ID;
}

