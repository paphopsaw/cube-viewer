#include "Slice.h"


Slice::Slice (Array2D* data, Axis axis, float loc) {
    location = loc;
    this->axis = axis;
    this->data = data;
    loadVertexData();
    loadTexture();
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

void Slice::loadTexture() {
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    std::cout << data->getData()->size() << "\n";
    std::cout << data->getN1() << "\n";
    std::cout << data->getN2() << "\n";
    glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, data->getN2(), data->getN1(), 0, GL_RED, GL_FLOAT, data->getData()->data());
    glGenerateMipmap(GL_TEXTURE_2D);
}
