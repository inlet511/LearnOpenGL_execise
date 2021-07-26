#version 330 core
in vec3 ourColor;
in vec2 uv;
out vec4 FragColor;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mix_rate;

void main() { 
	FragColor = mix(texture(texture1, uv), texture(texture2, vec2(1.0 - uv.s,uv.t)), mix_rate);
};