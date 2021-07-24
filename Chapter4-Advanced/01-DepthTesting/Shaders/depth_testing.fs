#version 460 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

float near = 0.1;
float far = 10.0;

float LinearizeDepth()
{
	// solution1 
	float z_ndc = gl_FragCoord.z * 2.0 -1.0;
	float z_clip = z_ndc/gl_FragCoord.w;
	float depth2 = (z_clip + near)/(near + far);


	//solution2
	float depth3 = (2.0 * near * far)/(far + near - z_ndc*(far - near));	
	depth3 /= far;
	return depth3;
}

void main()
{    
    FragColor = vec4(vec3(LinearizeDepth()),1.0);
}