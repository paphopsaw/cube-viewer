#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

uniform float location;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;


void main() {
    vec3 pos = vec3(aPos.x, aPos.y, aPos.z + location);
    gl_Position = proj * view * model * vec4(pos, 1.0);
    texCoord = aTexCoord;
}