#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec3 offsets[100];

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	vec3 offset = offsets[gl_InstanceID];
	gl_Position = projection * view * model *vec4(aPos + offset, 1.0);
}