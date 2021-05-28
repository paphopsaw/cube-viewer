#include "Slice.h"


Slice::Slice (Axis axis, float loc) {
    location = loc;
    this->axis = axis;
    loadVertexData();

    glGenTextures(1, &textureID);
    setupMesh();
}
void Slice::move(float delta) {
    location += delta;
}
void Slice::draw(Shader &shader) {
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shader.getId(), "sliceTexture"), 0);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glBindVertexArray(0);
}

void Slice::setupMesh() {
    unsigned int vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *) (3 * sizeof(float)));

    glBindVertexArray(0);

}

void Slice::loadVertexData() {
    if (axis == XY) {
            vertices = {
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
                 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
                -1.0f, -1.0f, 0.0f, 0.0f, 0.0f
            };


        } else if (axis == YZ) {
            vertices = {
                0.0f,  1.0f,  1.0f, 1.0f, 0.0f,
                0.0f,  1.0f, -1.0f, 1.0f, 1.0f,
                0.0f, -1.0f, -1.0f, 0.0f, 1.0f,
                0.0f, -1.0f, -1.0f, 0.0f, 1.0f,
                0.0f, -1.0f,  1.0f, 0.0f, 0.0f,
                0.0f,  1.0f,  1.0f, 1.0f, 0.0f
            };
        } else if (axis == ZX) {
            vertices = {
                -1.0f, 0.0f, -1.0f, 0.0f, 1.0f,
                 1.0f, 0.0f, -1.0f, 1.0f, 1.0f,
                 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,
                 1.0f, 0.0f,  1.0f, 1.0f, 0.0f,
                -1.0f, 0.0f,  1.0f, 0.0f, 0.0f,
                -1.0f, 0.0f, -1.0f, 0.0f, 1.0f
            };
        }
}

void Slice::loadTexture(std::vector<float>* data, int n0, int n1) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, n1, n0, 0, GL_RED, GL_FLOAT, data->data());
    glGenerateMipmap(GL_TEXTURE_2D);
}
