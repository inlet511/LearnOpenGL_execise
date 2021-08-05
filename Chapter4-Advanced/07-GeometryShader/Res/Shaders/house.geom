#version 330 core

layout (points) in;
layout (triangle_strip, max_vertices = 5) out;

in vec3 color[];

out vec3 fColor;

void main() {

    fColor = color[0];

    gl_Position = gl_in[0].gl_Position + vec4(-0.2, -0.2, 0.0, 0.0); 
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4( 0.2, -0.2, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4( -0.2, 0.2, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4( 0.2, 0.2, 0.0, 0.0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + vec4( 0.0, 0.4, 0.0, 0.0);

    fColor = vec3(1.0,1.0,1.0);
    EmitVertex();

    

    EndPrimitive();

    
}