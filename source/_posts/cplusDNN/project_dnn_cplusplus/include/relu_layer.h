

#pragma once
#ifndef RELU_H_
#define RELU_H_

#include<iostream>
#include<vector>
#include<cmath>
#include "base_layer.h"
using namespace std;

class Relu: public layer{
    public:
    Relu();
    virtual ~Relu();
    void forward(matrix &input_matrix, matrix &output_matrix);
    void backward(matrix &x_matrix, matrix &y_matrix, matrix &delta_matrix);
    
};

#endif