#version 460 core

struct Material{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct Light{
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	float constant;
	float linear;
	float quadratic;

};
 
uniform Material material;
uniform Light light;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

out vec4 FragColor;

uniform vec3 viewPos;


void main()
{

	vec3 lightDir = normalize(light.position - FragPos);

	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff)/epsilon,0.0,1.0);

		// Ambient
		vec3 ambient = light.ambient * texture(material.diffuse,TexCoords).rgb;
	
		// Diffuse
		vec3 norm = normalize(Normal);
		
		float diff = max(dot(norm,lightDir),0.0);
		vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;
	
		// Specular
		vec3 reflectVec = -reflect(lightDir,norm);
		vec3 viewDir = normalize(viewPos-FragPos);
		float spec = pow(max(dot(reflectVec,viewDir),0.0),material.shininess);
		vec3 specular = texture(material.specular, TexCoords).rgb * spec * light.specular;




		// apply attenuation
		float distance = length(light.position - FragPos);
		float attenuation = 1.0/(light.constant + light.linear * distance + light.quadratic * distance * distance);
		ambient *= attenuation;
		diffuse *= attenuation;
		specular *= attenuation;

		// Spot light
		diffuse *= intensity;
		specular *= intensity;

		vec3 result = ambient + diffuse + specular;

		FragColor =  vec4(result,1.0);


	
}