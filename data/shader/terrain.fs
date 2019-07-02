#version 330 core



out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

vec3 CalcDirLight();

void main(){
	
	FragColor = vec4(CalcDirLight(), 1.0);
}

vec3 CalcDirLight()
{
    vec3 lightDir = normalize(-vec3(1.0, 0.5, 1.0));
    // diffuse shading
    float diff = max(dot(Normal, lightDir), 0.0);
    // specular shading
    //vec3 reflectDir = reflect(-lightDir, Normal);
    //float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    // combine results
    vec3 ambient  = vec3(0.1, 0.1, 0.1)  * vec3(0.8, 0.4, 0.2);
    vec3 diffuse  = vec3(0.5, 0.5, 0.5)  * diff * vec3(0.8, 0.4, 0.2);
    //vec3 specular = vec3(1.0, 1.0, 1.0) * spec * vec3(1.0, 1.0, 1.0);

    return (ambient + diffuse);
}  