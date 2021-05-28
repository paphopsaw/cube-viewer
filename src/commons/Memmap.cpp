#include "Memmap.h"

Array3D::Array3D(const char* fileName, int n0, int n1, int n2) {
    int fd = open(fileName, O_RDONLY);
    size = lseek(fd, 0, SEEK_END);
    filePtr = static_cast<float*>(mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0));
    shape.n0 = n0;
    shape.n1 = n1;
    shape.n2 = n2;
}

Array3D::~Array3D() {
    munmap(filePtr, size);
}

void Array3D::slice(int dim, int loc, std::vector<float>* sliceVector) {
    int n0 = shape.n0;
    int n1 = shape.n1;
    int n2 = shape.n2;

    if (isValidSlice(dim, loc)) {
        if (dim == 0) {
            int sliceSize = n1 * n2;
            sliceVector->reserve(sliceSize);
            sliceVector->clear();
            for (int i = 0; i < sliceSize; i++) {
                sliceVector->push_back(readFloat(loc * sliceSize + i));
            }
            
        } else if (dim == 1) {
            int sliceSize = n0 * n2;
            sliceVector->reserve(sliceSize);
            sliceVector->clear();
            for (int i = 0; i < sliceSize; i++) {
                sliceVector->push_back(readFloat((loc + (i / n2) * n1) * n2 + (i % n2)));
            }
        } else if (dim == 2) {
            int sliceSize = n0 * n1;
            sliceVector->reserve(sliceSize);
            sliceVector->clear();
            for (int i = 0; i < sliceSize; i++) {
                sliceVector->push_back(readFloat(loc + i * n2));
            }
        }
    }
}


Shape Array3D::getShape() {
    return shape;
}

float Array3D::readFloat(int pos) {
    float f;
    std::memcpy(&f, filePtr + pos, sizeof(float));
    return f;
}

bool Array3D::isValidSlice(int dim, int loc) {
    if (dim < 0 || dim > 2) {
        std::cout << "ERROR: 3D array only has dimesion 0, 1, or 2\n";
        return false;
    }
    int maxDim;
    if (dim == 0)
        maxDim = shape.n0;
    else if (dim == 1)
        maxDim = shape.n1;
    else if (dim == 2)
        maxDim = shape.n2;

    if (loc < 0 || loc > maxDim - 1) {
        std::cout << "ERROR: Invalid index for dimension " << dim << "\n";
        return false;
    }
    return true;
}