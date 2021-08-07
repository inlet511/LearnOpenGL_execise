#version 330 core

in vec2 texCoords;
flat in int id;
out vec4 FragColor;

uniform sampler2D diff_sampler;


void main()
{
	vec3 color_variant = vec3(id/100.0, 1-id/100.0, abs(0.5-id/100));
	FragColor = vec4(texture(diff_sampler, texCoords).rgb * color_variant, 1.0);
}