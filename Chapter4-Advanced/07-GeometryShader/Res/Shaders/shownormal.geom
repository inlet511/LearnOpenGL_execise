#version 330 core

layout (triangles) in;
layout (line_strip, max_vertices = 2) out;

in VS_OUT{
    vec3 normal;
}gs_in[];



void main() {

    float normalLength = 0.1f;
    vec3 start = ((gl_in[0].gl_Position + gl_in[1].gl_Position + gl_in[2].gl_Position)/3.0).xyz;
    vec3 normal = normalize((gs_in[0].normal + gs_in[1].normal + gs_in[2].normal)/3.0);
    vec3 end =  start + normal * normalLength;

    gl_Position = vec4(start,1.0);
    EmitVertex();

    gl_Position = vec4(end,1.0);
    EmitVertex();

    EndPrimitive();
}