#version 330 core

out vec4 FragColor;

in vec3 color;
in vec2 TexCoord;

uniform sampler2D texture;

void main(){
	//FragColor =  vec4(color, 1.0); 
	FragColor = texture(texture, TexCoord);
}