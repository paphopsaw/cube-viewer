#ifndef SLICE_H
#define SLICE_H


#include "Shader.h"
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
    //Remove data from here
    Slice (Axis axis, float loc = 0.0f);
    void move(float delta);
    void draw(Shader &shader);
    void loadTexture(std::vector<float>* data, int n1, int n2);

private:
    unsigned int vao;
    unsigned int textureID;
    Axis axis;
    float location;
    std::vector<float> vertices;
    //Maybe use one set of vertex and transform using model matrix instead
    void loadVertexData();
    void setupMesh();
};

#endif