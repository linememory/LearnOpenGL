#version 330 core

layout(location = 0) in vec3 aPos; 
layout(location = 1) in vec2 aTexCoord;

out vec3 color;
out vec2 TexCoord;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main() {
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	//gl_Position = model * vec4(aPos, 1.0);
	color = vec3(0.5, 0.9, 0.5);
	TexCoord = aTexCoord;
}