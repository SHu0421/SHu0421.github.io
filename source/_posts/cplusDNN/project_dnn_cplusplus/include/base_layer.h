#pragma once

#ifndef LAYER_H_
#define LAYER_H_
#include<iostream>
#include <vector> // #include directive
#include <string>
using namespace std;


struct matrix{
    vector<vector<vector<vector<float>>>> value;
    matrix();
    virtual ~matrix();
    matrix(int b, int c, int s, bool rand_flag);
};

    

class layer{
    public:
    string type;
    layer();
    virtual ~layer();
    virtual void forward(matrix &input_matrix, matrix &output_matrix);
    virtual void backward(matrix &x_matrix, matrix &y_matrix, matrix &delta_matrix);
};


#endif
