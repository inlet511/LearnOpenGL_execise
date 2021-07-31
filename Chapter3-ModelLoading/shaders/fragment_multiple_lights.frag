#version 330 core
in vec3 normal;
in vec3 worldPos;
in vec2 TexCoords;

out vec4 FragColor;


struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight
{
	vec3 position;

	vec3 direction;
	float outerCone;
	float fallOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

#define NR_POINT_LIGHTS 4

uniform vec3 viewPos;
uniform DirectionalLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotlight;
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform float shininess;

// function prototypes
vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() { 
	vec3 N = normalize(normal);
	vec3 V = normalize(viewPos - worldPos);

	vec3 result = CalcDirLight(dirLight, N, V);
	
	
	for(int i = 0 ; i<NR_POINT_LIGHTS; i++)
	{
		result += CalcPointLight(pointLights[i], N, worldPos, V);
	}
	
	result +=  CalcSpotLight(spotlight, N, worldPos, V);
	
	FragColor = vec4(result,1.0);
};

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{	
	vec3 L = normalize(-light.direction);

	// diffuse
	float diff = max(dot(normal,L),0.0);
	vec3 reflectDir = reflect(-L,normal);

	// specular
	float spec = pow(max(dot(viewDir, reflectDir),0.0), shininess);

	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1,TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(texture_specular1, TexCoords));

	return ambient + diffuse + specular;
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - worldPos);

	float diff = max(dot(normal, lightDir),0.0);

	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);

	float distance = length(light.position - worldPos);

	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	vec3 ambient = light.ambient * vec3(texture(texture_diffuse1, TexCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(texture_diffuse1,TexCoords));
	vec3 specular = light.specular * spec * vec3(texture(texture_specular1,TexCoords));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return ambient + diffuse + specular;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 L = normalize(light.position - worldPos);
	vec3 SpotDirection = normalize(-light.direction);
	vec3 R = reflect(-L, normal);

	float theta = dot(SpotDirection,L);

	vec3 ambient = light.ambient * texture(texture_diffuse1, TexCoords).rgb;

	float diff =  max(dot(L,normal),0.0);
	vec3 diffuse = light.diffuse * diff * texture(texture_diffuse1, TexCoords).rgb;
	
	vec3 EyeDirection = normalize(viewPos - worldPos);
	float spec = pow(max(dot(R,EyeDirection),0.0),shininess);
	vec3 specular = light.specular * spec * texture(texture_specular1,TexCoords).rgb;

	float distance = length(worldPos - light.position);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	float epsilon = light.fallOff * attenuation * attenuation;//让距离也参与影响灯光边界的衰减
	float intensity = clamp((theta - light.outerCone )/epsilon, 0.0,1.0);

	diffuse *= intensity;
	specular*= intensity;
	return attenuation*(ambient + diffuse + specular);


}