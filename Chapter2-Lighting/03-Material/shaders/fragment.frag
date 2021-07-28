#version 330 core

struct Material{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

in vec3 worldPos;
in vec3 normal;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor;
uniform vec3 eyePos;
uniform Material material;

void main() { 

	vec3 ambient = lightColor * material.ambient;

	vec3 N = normalize(normal);
	vec3 L = normalize(lightPos-worldPos);

	vec3 diffuse = lightColor * (max(dot(L,N),0.0) * material.diffuse);

	vec3 R = reflect(-L, N);
	vec3 EyeDirection = normalize(eyePos - worldPos);
	vec3 specular = lightColor * (pow(max(dot(R,EyeDirection),0.0),material.shininess) * material.specular);

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result,1.0);
};