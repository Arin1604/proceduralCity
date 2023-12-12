#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 UVposition;


out vec2 UVpos;
void main() {
    UVpos = UVposition;
    gl_Position = vec4(position, 1.0);
}
