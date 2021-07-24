#version 460 core

out vec4 FragColor;

in vec3 Normal;
in vec3 Position;

uniform vec3 camPos;
uniform samplerCube skybox;


void main()
{
	float refrecRatio = 1.00/1.52;
    vec3 I = normalize(Position - camPos);
    vec3 R = refract(I, normalize(Normal),refrecRatio);
    FragColor = vec4(texture(skybox, R).rgb, 1.0);
}