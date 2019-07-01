#version 330 core

layout(location = 0) in vec3 aPos; 

out vec3 FragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;
uniform float time;

void main() {
	FragPos = vec3(model * vec4(aPos, 1.0));
	vec3 pos = vec3(aPos.x, sin(aPos.x + time)*0.2, aPos.z);
	
	gl_Position = projection * view * model * vec4(pos, 1.0);
}