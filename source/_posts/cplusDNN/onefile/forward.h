#ifndef FORWARD_H
#define  FORWARD_H
#include<iostream>
#include <vector> // #include directive
#include <string>
using namespace std;
struct matrix{
    vector<vector<vector<vector<float>>>> value;
    matrix();
    matrix(int b, int c, int s);
};

    

class layer{
    public:
    string type;
    layer();
    virtual ~layer();
    virtual void forward(matrix &input_matrix, matrix &output_matrix);
};

class Conv: public layer{
    public:
    Conv();
   virtual  ~Conv();
    Conv(int in_c, int out_c, int k_size,  int s, int p);
    void forward(matrix &input_matrix, matrix &output_matrix);
};

class BN: public layer{
    public:
    BN();
    virtual ~BN();
    BN(float g, float b, float e);
    void initWeight();
    void forward(matrix &input_matrix, matrix &output_matrix);
};

class Relu: public layer{
    public:
    Relu();
    virtual ~Relu();
    void forward(matrix &input_matrix, matrix &output_matrix);
};

#endif
