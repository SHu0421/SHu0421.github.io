
#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include "conv_layer.h"
using namespace std;


Conv::Conv(){
    type="conv";
};
Conv::~Conv(){};
Conv::Conv(int in_c, int out_c, int k_size,  int s, int p){
    w_matrix =  matrix(out_c, in_c, k_size, true);
    type="conv";
    in_channel=in_c;
    out_channel=out_c;
    kernel_size=k_size;
    stride=s;
    padding=p; //加在输入，不是weight上

    bias=vector<float>(out_c);
    
}

//计算一个卷积核进行一次卷积的过程
float Conv::computeOneKernel(vector<vector<vector<float>>> &input, vector<vector<vector<float>>> &weight, int m, int n, 
    int channel, int in_size, int w_size, int stride, int padding){
    float ans=0;
    for(int k=0;k<channel;k++){
        for(int i=0;i<w_size;i++){
            for(int j=0;j<w_size;j++){
                if(m*stride+i-padding>=0&&n*stride+j-padding>=0&&m*stride+i-padding<in_size&&n*stride+j-padding<in_size){
                    ans+=input[k][m*stride+i-padding][n*stride+j-padding]*weight[k][i][j];
                }
            }
        } 
    }
    return ans;
}
void Conv::forward(matrix &input_matrix, matrix &output_matrix){
    vector<vector<vector<vector<float>>>> &input=input_matrix.value;
    
    vector<vector<vector<vector<float>>>> &weight=w_matrix.value;
    int in_b = input.size();
    int in_c=input[0].size(); 
    int in_size=input[0][0].size();

    int w_size=weight[0][0].size();

    int out_b = in_b;
    int out_c=out_channel; 
    int out_size=(in_size-w_size+2*padding)/stride+1;

    cout<<"enter conv layer"<<endl;
    cout<<"input shape:["<<in_b<<","<<in_c<<","<<in_size<<","<<in_size<<"]"<<endl;
    cout<<"output shape:["<<out_b<<","<<out_c<<","<<out_size<<","<<out_size<<"]"<<endl;
    cout<<"weight shape:["<<out_c<<","<<in_c<<","<<w_size<<","<<w_size<<"]"<<
    " kernel_size: "<< kernel_size<<" stride: "<< stride <<" padding: "<< padding<< endl;

    vector<vector<vector<vector<float>>>> &res=output_matrix.value;
    res.resize(out_b);
    for (int i = 0; i < out_b; ++i) {
        res[i].resize(out_c);
        for (int j = 0; j < out_c; ++j){
            res[i][j].resize(out_size);
            for(int k = 0;k < out_size; k++){
                res[i][j][k].resize(out_size);
            }
        }     
    }
    for(int batch=0; batch<out_b;batch++){
        for(int num=0;num<out_c;num++){
            for(int m=0;m<out_size;m++){
                for(int n=0;n<out_size;n++){
                    float oneNum = computeOneKernel(input[batch], weight[num],  m, n,  in_c, in_size, w_size, stride, padding);
                    // cout<<oneNum<<endl;
                    res[batch][num][m][n]= oneNum + bias[num];
                }
            }
        }
    }
    cout<<"return from conv layer"<<endl;

}



void Conv::backward(matrix &x_matrix, matrix &y_matrix, matrix &delta_matrix){
    cout<<"TODO: implement the backward function for conv layer"<<endl;
}


