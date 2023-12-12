#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 norm;

out vec3 world_pos_out;
out vec3 world_norm_out;

uniform mat4 modelM;
uniform mat4 MVP;

void main() {    
    world_pos_out = vec3(modelM * vec4(position, 1));
    world_norm_out = normalize(inverse(transpose(mat3(modelM))) * normalize(norm));
    gl_Position = MVP * vec4(position, 1);
}

