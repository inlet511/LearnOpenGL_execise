#version 330 core

in vec3 viewPos;
in vec3 normal;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos_viewspace;
uniform vec3 eyePos_viewspace;
uniform float Shininess;
uniform float specularMultiplier;

void main() { 
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;	

	vec3 N = normalize(normal);
	vec3 L = normalize(lightPos_viewspace-viewPos);

	vec3 diffuse = max(dot(L,N),0.0) * lightColor;

	vec3 R = reflect(-L, N);
	vec3 EyeDirection = normalize(eyePos_viewspace - viewPos);
	vec3 specular = pow(max(dot(R,EyeDirection),0.0),Shininess) * lightColor * specularMultiplier;

	vec3 result = (ambient + diffuse+specular) * objectColor;

	FragColor = vec4(result,1.0);
};