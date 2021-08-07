#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;
layout (location = 2) in vec3 aOffset;


out vec2 texCoords;
flat out int id;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	texCoords = aTexCoords;
	id = gl_InstanceID;
	gl_Position = projection * view * model *vec4(aPos + aOffset, 1.0);
}