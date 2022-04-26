#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include "base_layer.h"
using namespace std;


matrix::matrix(){};
matrix::~matrix(){};
matrix::matrix(int b, int c, int s, bool rand_flag=true){
    value = vector<vector<vector<vector<float>>>>(b, vector<vector<vector<float>>>(c, vector<vector<float>>(s, vector<float>(s, 0))));
    if(rand_flag){
        for(int i=0;i<b;i++){
            for(int j=0;j<c;j++){
                for(int k=0;k<s;k++){
                    for(int q=0;q<s;q++){
                        value[i][j][k][q]=rand();
                    }
                }
            }
        }
    }
    
};

   


layer::layer(){};
layer::~layer(){};
void layer::forward(matrix &input_matrix, matrix &output_matrix){
    cout<<"enter father layer forward function"<<endl;
};

void layer::backward(matrix &x_matrix, matrix &y_matrix, matrix &delta_matrix){
    cout<<"enter father layer backward function"<<endl;
}







