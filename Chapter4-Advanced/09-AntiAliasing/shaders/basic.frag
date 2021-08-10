#version 330 core
in vec3 worldPos;
in vec2 TexCoords;

out vec4 FragColor;


uniform sampler2D diff_tex;

void main() {
	vec4 texColor = texture(diff_tex, TexCoords);
	if(texColor.a < 0.1)
	{
		discard;
	}
	FragColor = texColor;
};