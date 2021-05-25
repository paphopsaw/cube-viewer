#ifndef SLICE_H
#define SLICE_H


#include "Shader.h"
#include "ArrayData.h"
#include <glad/glad.h>
#include <vector>
#include <iostream>

enum Axis {
    XY,
    YZ,
    ZX,
};

class Slice {
public:
    Slice (Array2D* data, Axis axis, float loc = 0.0f);
    void move(float delta);
    void draw(Shader &shader);

private:
    unsigned int vao;
    unsigned int textureID;
    Array2D* data;
    Axis axis;
    float location;
    std::vector<float> vertices;
    void loadVertexData();
    void loadTexture();
    void setupMesh();
};

#endif