


#pragma once
#ifndef CONV_BN_RELU_H_
#define CONV_BN_RELU_H_

#include<iostream>
#include<vector>
#include<cmath>
#include "conv_layer.h"

using namespace std;

class Conv_BN_Relu: public Conv{
    public:
    Conv_BN_Relu();
    Conv_BN_Relu(Conv *father);
    virtual ~Conv_BN_Relu();
    float computeOneKernel(vector<vector<vector<float>>> &input, vector<vector<vector<float>>> &weight, int m, int n, 
    int channel, int in_size, int w_size, int stride, int padding);
    void forward_fusion(matrix &input_matrix, matrix &output_matrix, vector<float> &mean, vector<float> &stdvar, float epislon, float gamma, float beta);
    void backward(matrix &x_matrix, matrix &y_matrix, matrix &delta_matrix);
};

#endif