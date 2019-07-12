#version 330 core

out vec4 FragColor;
struct Material {
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform Material material;
uniform vec4 color;

in vec3 Normal;
in vec2 TexCoords;

void main(){
	FragColor = color + texture(material.diffuse, TexCoords);
	vec3 normal = normalize(Normal);
	vec3 DirLight = normalize(vec3(0.8, 1.0, 0.0));
	float diff = max(dot(normal, DirLight), 0.1);
	FragColor =  diff * vec4(vec3(1.0), 1.0); 
}