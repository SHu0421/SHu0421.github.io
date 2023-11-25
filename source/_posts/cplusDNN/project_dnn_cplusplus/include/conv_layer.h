


#pragma once
#ifndef CONV_H_
#define CONV_H_

#include<iostream>
#include<vector>
#include<cmath>
#include "base_layer.h"
using namespace std;

class Conv: public layer{
    public:
    int in_channel,  out_channel,  kernel_size,   stride,  padding;
    matrix w_matrix;
    vector<float> bias;

    Conv();
   virtual  ~Conv();
    Conv(int in_c, int out_c, int k_size,  int s, int p);
    float computeOneKernel(vector<vector<vector<float>>> &input, vector<vector<vector<float>>> &weight, int m, int n, 
    int channel, int in_size, int w_size, int stride, int padding);
    void forward(matrix &input_matrix, matrix &output_matrix);
    void backward(matrix &x_matrix, matrix &y_matrix, matrix &delta_matrix);
};

#endif