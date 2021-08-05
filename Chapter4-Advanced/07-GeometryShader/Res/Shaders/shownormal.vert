#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out VS_OUT{
    vec3 normal;
}vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vs_out.normal = (projection * view * transpose(inverse( model)) * vec4(aNormal,1.0)).xyz;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}