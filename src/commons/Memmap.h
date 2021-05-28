#ifndef MEMMAP_H
#define MEMMAP_H

#include <iostream>
#include <vector>
#include <cstring>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <cstdio>

struct Shape {
    int n0;
    int n1;
    int n2;
};

class Array3D {
public: 
    Array3D(const char* fileName, int n0, int n1, int n2);
    ~Array3D();
    void slice(int dim, int loc, std::vector<float>* sliceVector);
    Shape getShape();

private:
    float* filePtr;
    int dimension;
    int location;
    off_t size;
    Shape shape;

    float readFloat(int pos);
    bool isValidSlice(int dim, int loc);
};

#endif