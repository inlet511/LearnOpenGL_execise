#version 330 core

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

struct Light{
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 worldPos;
in vec3 normal;

out vec4 FragColor;

uniform vec3 eyePos;
uniform Material material;
uniform Light light;

void main() { 

	vec3 ambient = light.ambient * material.ambient;

	vec3 N = normalize(normal);
	vec3 L = normalize(light.position-worldPos);

	vec3 diffuse = light.diffuse * (max(dot(L,N),0.0) * material.diffuse);
	
	vec3 EyeDirection = normalize(eyePos - worldPos);
	vec3 H = normalize(L+EyeDirection);

	vec3 specular = light.specular * (pow(max(dot(N,H),0.0),material.shininess) * material.specular);

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result,1.0);
};