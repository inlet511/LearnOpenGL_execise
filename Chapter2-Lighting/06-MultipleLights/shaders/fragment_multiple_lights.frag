#version 330 core
in vec3 normal;
in vec3 worldPos;
in vec2 texCoords;

out vec4 FragColor;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

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
uniform Material material;

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
	//vec3 result =  CalcSpotLight(spotlight, N, worldPos, V);
	
	FragColor = vec4(result,1.0);
};

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{	
	vec3 L = normalize(-light.direction);

	// diffuse
	float diff = max(dot(normal,L),0.0);
	vec3 reflectDir = reflect(-L,normal);

	// specular
	float spec = pow(max(dot(viewDir, reflectDir),0.0), material.shininess);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,texCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular, texCoords));

	return ambient + diffuse + specular;
}


vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - worldPos);

	float diff = max(dot(normal, lightDir),0.0);

	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	float distance = length(light.position - worldPos);

	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

	vec3 ambient = light.ambient * vec3(texture(material.diffuse, texCoords));
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse,texCoords));
	vec3 specular = light.specular * spec * vec3(texture(material.specular,texCoords));

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

	vec3 ambient = light.ambient * texture(material.diffuse, texCoords).rgb;

	float diff =  max(dot(L,normal),0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, texCoords).rgb;
	
	vec3 EyeDirection = normalize(viewPos - worldPos);
	float spec = pow(max(dot(R,EyeDirection),0.0),material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular,texCoords).rgb;

	float distance = length(worldPos - light.position);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	float epsilon = light.fallOff * attenuation * attenuation;//让距离也参与影响灯光边界的衰减
	float intensity = clamp((theta - light.outerCone )/epsilon, 0.0,1.0);

	diffuse *= intensity;
	specular*= intensity;
	return attenuation*(ambient + diffuse + specular);


}