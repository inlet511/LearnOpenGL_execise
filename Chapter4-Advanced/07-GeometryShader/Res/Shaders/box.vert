#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    normal = (transpose(inverse(model)) * vec4(aNormal,1.0)).xyz;
    TexCoords = aTexCoords;

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}