#version 330 core

out vec4 FragColor;
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material material;

in vec3 Normal;
in vec2 TexCoords;

void main(){
	FragColor =  vec4(vec3(0.5), 1.0); 
	FragColor = texture(material.diffuse, TexCoords);
}