
#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include "conv_bn_relu.h"
using namespace std;


Conv_BN_Relu::Conv_BN_Relu(){};
Conv_BN_Relu::~Conv_BN_Relu(){};

Conv_BN_Relu::Conv_BN_Relu(Conv *father){
    w_matrix = father->w_matrix;
    type="conv_bn_relu";
    in_channel=father->in_channel;
    out_channel=father->out_channel;
    kernel_size=father->kernel_size;
    stride=father->stride;
    padding=father->padding; //加在输入，不是weight上
    bias=vector<float>(father->out_channel);
}
void Conv_BN_Relu::forward_fusion(matrix &input_matrix, matrix &output_matrix, vector<float> &mean, vector<float> &variance, float epislon, float gamma, float beta){

    cout<<"enter Conv_BN_Relu:: forward_fusion function"<<endl;
    vector<vector<vector<vector<float>>>> &input=input_matrix.value;
    vector<vector<vector<vector<float>>>> &weight=w_matrix.value;
    int in_b = input.size();
    int in_c=input[0].size(); 
    int in_size=input[0][0].size();


    int w_size=weight[0][0].size();

    int out_b = in_b;
    int out_c=out_channel; 
    int out_size=(in_size-w_size+2*padding)/stride+1;

    cout<<"input shape:["<<in_b<<","<<in_c<<","<<in_size<<","<<in_size<<"]"<<endl;
    cout<<"output shape:["<<out_b<<","<<out_c<<","<<out_size<<","<<out_size<<"]"<<endl;
    cout<<"weight shape:["<<out_c<<","<<in_c<<","<<w_size<<","<<w_size<<"]"<<
    " kernel_size: "<< kernel_size<<" stride: "<< stride <<" padding: "<< padding<< endl;

    // output_matrix=matrix(out_b, out_c, out_size);
    vector<vector<vector<vector<float>>>> &res=output_matrix.value;
    res.resize(out_b);
    for (int i = 0; i < out_b; ++i) {
        res[i].resize(out_c);
        for (int j = 0; j < out_c; ++j){
            res[i][j].resize(out_size);
            for(int k = 0;k < out_size; k++){
                res[i][j][k].resize(out_size);
                // cout<<i<<" "<<j<<" "<<k<<" resize"<<endl;
            }
        }     
    }
    for(int batch=0; batch<out_b;batch++){
        for(int num=0;num<out_c;num++){
            for(int m=0;m<out_size;m++){
                for(int n=0;n<out_size;n++){
                    float oneNum = Conv::computeOneKernel(input[batch], weight[num],  m, n,  in_c, in_size, w_size, stride, padding);
                    // cout<<oneNum<<endl;
                    //  w = w * (gamma / var_sqrt)
                    // b = (b - mean)/var_sqrt * gamma + beta
                    float tmp=oneNum*(gamma/ sqrt(variance[num]+epislon))  + (bias[num]-mean[num])/sqrt(variance[num]+epislon)+beta;
                    if(tmp>0){
                        res[batch][num][m][n]= tmp;
                    }else{
                        res[batch][num][m][n]= 0;
                    }
                }
            }
        }
    }
    cout<<"return from conv_bn_relu layer"<<endl;
}


void Conv_BN_Relu::backward(matrix &x_matrix, matrix &y_matrix, matrix &delta_matrix){
    cout<<"Conv_BN_Relu only use in forward, no backward function"<<endl;
}
