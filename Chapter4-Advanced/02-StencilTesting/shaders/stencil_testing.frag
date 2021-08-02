#version 330 core
in vec3 worldPos;
in vec2 TexCoords;

out vec4 FragColor;

float far = 10.0;
float near = 0.1;

uniform sampler2D diff_tex;

void main() {


	FragColor = vec4(texture(diff_tex,TexCoords).rgb,1.0);
};