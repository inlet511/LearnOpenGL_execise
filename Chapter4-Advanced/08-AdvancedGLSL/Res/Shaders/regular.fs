#version 460 core

out vec4 FragColor;

in vec3 Color;
in vec3 Position;

uniform vec3 camPos;
uniform samplerCube skybox;


void main()
{
    FragColor = vec4(Color,1.0); 
}
