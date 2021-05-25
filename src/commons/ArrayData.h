#ifndef ARRAY_DATA_H
#define ARRAY_DATA_H

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

class Array2D
{
public:
    Array2D(const char* fileName, int n1, int n2);
    std::vector<float>* getData();
    int getN1();
    int getN2();
    float getMax();
    float getMin();
    float getMean();
    float getSd();

private:
    std::vector<float> data;
    int n1;
    int n2;
    float max;
    float min;
    float mean;
    float sd;
};


#endif