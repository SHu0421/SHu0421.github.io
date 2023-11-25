#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include "relu_layer.h"
using namespace std;

Relu::Relu(){
    type="relu";
};
Relu::~Relu(){};
void Relu::forward(matrix &input_matrix, matrix &output_matrix){
    vector<vector<vector<vector<float>>>> &input=input_matrix.value;
    int batch_size=input.size();
    int channel_size=input[0].size(); // channel size
    int m_size=input[0][0].size();
    vector<vector<vector<vector<float>>>> &res=output_matrix.value;

    cout<<"enter Relu layer"<<endl;
    cout<<"input shape:["<<batch_size<<","<<channel_size<<","<<m_size<<","<<m_size<<"]"<<endl;

    res.resize(batch_size);
    for (int i = 0; i < batch_size; ++i) {
        res[i].resize(channel_size);
        for (int j = 0; j < channel_size; ++j){
            res[i][j].resize(m_size);
            for(int k = 0;k < m_size; k++){
                res[i][j][k].resize(m_size);
            }
        }     
    }

    for(int b=0;b<batch_size;b++){
        for(int i=0;i<channel_size;i++){
            for(int j=0;j<m_size;j++){
                for(int k=0;k<m_size;k++){
                    if(input[b][i][j][k]<0){
                        res[b][i][j][k]=0;
                    }else{
                        res[b][i][j][k]=input[b][i][j][k];
                    }
                }
            }
        }
    }
}


void Relu::backward(matrix &x_matrix, matrix &y_matrix, matrix &delta_matrix){
    vector<vector<vector<vector<float>>>> &input=y_matrix.value;
    int batch_size=input.size();
    int hei_input=input[0].size(); // channel size
    int size_input=input[0][0].size();
    // output_matrix的初始化在调用这个函数那一层
    // vector<vector<vector<vector<float>>>> dx(batch_size, vector<vector<vector<float>>>(hei_input, vector<vector<float>>(size_input, vector<float>(size_input, 0))));
    vector<vector<vector<vector<float>>>> &dx=delta_matrix.value;

    for(int b=0;b<batch_size;b++){
        for(int i=0;i<hei_input;i++){
            for(int j=0;j<size_input;j++){
                for(int k=0;k<size_input;k++){
                    if(input[b][i][j][k]>0){
                        dx[b][i][j][k]=dx[b][i][j][k]*1;
                    }
                }
            }
        }
    }
}
