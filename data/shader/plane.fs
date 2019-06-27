#version 330 core

struct Material {
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light {
	vec3 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
};

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 viewPos;

uniform Material material;
uniform Light light;

void main(){

	// ambient 
	vec3 ambient = light.ambient * material.diffuse;

	
	vec3 lightDir = normalize(light.position - FragPos);
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * pow(distance, 2));

	float theta = dot(normalize(-light.direction), lightDir);
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// diffuse
	vec3 norm = normalize(Normal);
	

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * material.diffuse;

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * material.specular;

	ambient *= attenuation;
	diffuse *= attenuation * intensity;
	specular *= attenuation * intensity;
	FragColor =  vec4(ambient + diffuse + specular, 1.0);

	

	
	

	
}