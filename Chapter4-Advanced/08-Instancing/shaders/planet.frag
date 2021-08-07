#version 330 core
in vec2 texCoords;
out vec4 FragColor;

uniform sampler2D texture_diffuse1;

void main()
{
	FragColor = vec4(texture(texture_diffuse1, texCoords).rgb , 1.0);
}