#version 330 core

struct Material{
	sampler2D diffuseMap;
	sampler2D specularMap;
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
in vec2 uv;

out vec4 FragColor;

uniform vec3 eyePos;
uniform Material material;
uniform Light light;

void main() { 


	vec3 N = normalize(normal);
	vec3 L = normalize(light.position-worldPos);
	vec3 R = reflect(-L, N);

	vec3 ambient = light.ambient * texture(material.diffuseMap, uv).rgb;

	float diff =  max(dot(L,N),0.0) ;
	vec3 diffuse = light.diffuse * diff * texture(material.diffuseMap, uv).rgb;

	
	vec3 EyeDirection = normalize(eyePos - worldPos);
	float spec = pow(max(dot(R,EyeDirection),0.0),material.shininess);
	vec3 specular = light.specular * spec * texture(material.specularMap,uv).rgb;

	vec3 result = ambient + diffuse + specular;

	FragColor = vec4(result,1.0);
};