#include "ArrayData.h"

Array2D::Array2D(const char* fileName, int n1, int n2){
    int arraySize = n1 * n2;
    this->n1 = n1;
    this->n2 = n2;
    float f;
    std::ifstream fs(fileName, std::ios::binary);
    bool firstValue = true;

    float sum = 0;
    float sumSquare = 0;

    for (int i = 0; i < arraySize; i++) {
        fs.read(reinterpret_cast<char *>(&f), sizeof(f));

        if (firstValue) {
            min = f;
            max = f;
            firstValue = false;
        }
        if (f < min)
            min = f;
        else if (f > max)
            max = f;

        sum += f;
        sumSquare += (f * f);
        
        data.push_back(f);
    }
    mean = sum / arraySize;
    sd = std::sqrt(sumSquare / arraySize - (mean * mean));
}

std::vector<float>* Array2D::getData() {
    return &data;
}

float Array2D::getMax() {
    return max;
}

float Array2D::getMin() {
    return min;
}

float Array2D::getMean() {
    return mean;
}

float Array2D::getSd() {
    return sd;
}

int Array2D::getN1() {
    return n1;
}

int Array2D::getN2() {
    return n2;
}
