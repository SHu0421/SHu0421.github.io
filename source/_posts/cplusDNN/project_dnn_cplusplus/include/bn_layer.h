


#pragma once
#ifndef BN_H_
#define BN_H_

#include<iostream>
#include<vector>
#include<cmath>
#include "base_layer.h"
using namespace std;

class BN: public layer{
    public:
    float gamma;
    float beta;
    float epislon;
    vector<float> mean;
    vector<float> variance;
    BN();
    virtual ~BN();
    BN(float g, float b, float e, int size);
    void initWeight();
    void forward(matrix &input_matrix, matrix &output_matrix);
    void backward(matrix &x_matrix, matrix &y_matrix, matrix &delta_matrix);
};

#endif