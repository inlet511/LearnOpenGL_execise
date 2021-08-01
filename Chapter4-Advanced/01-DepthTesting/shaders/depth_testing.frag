#version 330 core
in vec3 worldPos;
in vec2 TexCoords;

out vec4 FragColor;

float far = 10.0;
float near = 0.1;

uniform sampler2D diff_tex;

void main() {

	float z = gl_FragCoord.z * 2.0 - 1.0; // back to NDC 
    float v =(2.0 * near * far) / (far + near - z * (far - near));
	v/=far;
	v=1.0-v;

	FragColor = vec4(v,v,v,1.0);
};