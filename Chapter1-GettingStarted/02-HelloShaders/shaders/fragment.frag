#version 330 core
in vec3 ourColor;
in vec3 vert_pos;
out vec4 FragColor;

void main() { 
	FragColor = vec4(vert_pos, 1.0); 
};