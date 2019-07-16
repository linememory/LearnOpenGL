#version 330 core

in vec3 Normal;
in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D texture0;

void main(){
	vec4 c = texture(texture0, TexCoords);
	if(c.a < 0.1)
		discard;
	FragColor = c; 
}