#version 330 core
out vec4 FragColor;

in vec3 normal;
in vec3 worldPos;
in vec2 TexCoords;

uniform samplerCube skybox;
uniform vec3 camPos;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_specular1;
uniform sampler2D texture_normal1;
uniform sampler2D texture_height1;

void main()
{   
    vec4 diff = texture(texture_diffuse1,TexCoords);
    float reflect_strength = texture(texture_height1, TexCoords).r;

    vec3 I = worldPos - camPos;
    vec3 R = reflect(I, normalize(normal));
    vec4 reflect_color = vec4(texture(skybox,R).rgb,1.0);

    FragColor = diff + reflect_color * reflect_strength;

}