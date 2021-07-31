#version 330 core
out vec4 FragColor;

in vec3 normal;
in vec3 worldPos;
in vec2 TexCoords;


struct DirectionalLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

vec3 CalcDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform DirectionalLight dirLight;
uniform float shininess;
uniform vec3 viewPos;

void main()
{    
	vec3 N = normalize(normal);
	vec3 V = normalize(viewPos - worldPos);
    vec4 tex = texture(texture_specular1, TexCoords);

	vec3 result = CalcDirLight(dirLight, N, V);
	FragColor = vec4(result,1.0);
}

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