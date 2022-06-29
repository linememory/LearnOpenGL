#include "TextureLoader.h"


std::vector<Texture> TextureLoader::texturesLoaded{};

unsigned int TextureLoader::textureFromFile(const char *path){
    unsigned int ID = 0;
	glGenTextures(1, &ID);
	int width, height, nrComponents;
    stbi_set_flip_vertically_on_load(true);
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

Texture TextureLoader::loadTexture(std::string path, TextureType type){
    for(auto t : TextureLoader::texturesLoaded){
        if(t.path == path && t.type == type)
            return t;
    }
    Texture texture{textureFromFile(path.c_str()), type, path};
    return texture;
}
