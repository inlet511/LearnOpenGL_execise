#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aUv;
out vec3 ourColor;
out vec2 uv;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float offset;

void main() {
  gl_Position = projection * view * model * vec4(aPos, 1.0);
  ourColor = aColor;
  uv = vec2(aUv.x, aUv.y);
};