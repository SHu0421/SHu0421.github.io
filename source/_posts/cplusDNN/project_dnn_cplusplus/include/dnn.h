
#pragma once
#ifndef DNN_H_
#define DNN_H_

#include<iostream>
#include<vector>
#include<cmath>
#include "base_layer.h"
using namespace std;


class DNN{
    public:
    vector<layer*> layers;
    vector<matrix> out_activations;
    bool fuse;//推理的时候是否需要将conv_bn_relu进行融合
    // float loss;
		DNN();
		virtual ~DNN();
		void initNet();
		void forward(matrix &input_matrix);
};

#endif



