#version 330 core

in vec2 texCoords;
out vec4 FragColor;

uniform sampler2D diff_sampler;

void main()
{
	FragColor = vec4(texture(diff_sampler, texCoords).rgb, 1.0);
}