#version 330 core
out vec4 FragColor;

in vec3 normal;
in vec3 worldPos;

uniform samplerCube skybox;
uniform vec3 camPos;

void main()
{   
    vec3 I = worldPos - camPos;
    vec3 R = reflect(I, normalize(normal));
    FragColor = texture(skybox,R);

}