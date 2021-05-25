#version 330 core
out vec4 FragColor;

in vec2 texCoord;
uniform sampler2D sliceTexture;

void main() {
    float temp = texture(sliceTexture, texCoord).r;
    FragColor = vec4(vec3(temp), 1.0f);
}