
#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include "bn_layer.h"
using namespace std;


BN::BN(){
    type="bn";
    gamma=1;
    beta=0;
    epislon=0.0000001;

};
BN::~BN(){};
BN::BN(float g, float b, float e, int size){
    type="bn";
    gamma=g;
    beta=b;
    epislon=e;
    mean.resize(size);
    variance.resize(size); //sigma^2
}
void BN::initWeight(){};
    
void BN::forward(matrix &input_matrix, matrix &output_matrix){
        vector<vector<vector<vector<float>>>> &input=input_matrix.value;
    int batch_size=input.size();
    int channel_size=input[0].size(); 
    int m_size=input[0][0].size();

    mean=vector<float>(channel_size, 0);
    variance=vector<float>(channel_size, 0);

    cout<<"enter BN layer"<<endl;
    cout<<"input shape:["<<batch_size<<","<<channel_size<<","<<m_size<<","<<m_size<<"]"<<endl;

    vector<vector<vector<vector<float>>>> &res=output_matrix.value;
    res.resize(batch_size);
    for (int i = 0; i < batch_size; ++i){
        res[i].resize(channel_size);
        for (int j = 0; j < channel_size; ++j){
            res[i][j].resize(m_size);
            for(int k = 0;k < m_size; k++){
                res[i][j][k].resize(m_size);
            }
        }     
    }

    for(int i=0;i<channel_size;i++){
        for(int j=0;j<m_size;j++){
            for(int k=0;k<m_size;k++){
                for(int b=0;b<batch_size;b++){
                    mean[i]+=input[b][i][j][k];
                }
            }
        }
        mean[i]=mean[i]/(batch_size*m_size*m_size);
    }
    for(int i=0;i<channel_size;i++){
        for(int j=0;j<m_size;j++){
            for(int k=0; k<m_size;k++){
                for(int b=0;b<batch_size;b++){
                    variance[i]+=(input[b][i][j][k]-mean[i])*(input[b][i][j][k]-mean[i]);
                }
            }
        }
    }

    for(int i=0;i<channel_size;i++){
        for(int j=0;j<m_size;j++){
            for(int k=0;k<m_size;k++){
                float stdvar=sqrt(variance[i]/(batch_size*m_size*m_size)+epislon);
                for(int b=0;b<batch_size;b++){
                    res[b][i][j][k]=(input[b][i][j][k]-mean[i])/stdvar;
                }
            }
        }
    }

}


// 这里是对论文中最后一个公式的缩放系数求梯度更新值 gamma
// x_norm 代表BN层前向传播的输出值
// delta 代表上一层的梯度图
// batch 为l.batch，即一个batch的图片数
// n代表输出通道数，也即是输入通道数
// size 代表w * h
// scale_updates 代表scale的梯度更新值
// y = gamma * x + beta
// dy / d(gamma) = x 
// 这个的作用是什么?
void compute_backward_scale(matrix &x_norm_matrix, matrix &delta_matrix, vector<float> &scale_updates)
{
    vector<vector<vector<vector<float>>>> &delta=delta_matrix.value;
    vector<vector<vector<vector<float>>>> &x_norm=x_norm_matrix.value;
    int batch_size=delta.size();
    int channel_input=delta[0].size(); // channel size
    int size_input=delta[0][0].size();

    for(int f = 0; f < channel_input; ++f){
        float sum = 0;
        for(int b = 0; b < batch_size; ++b){
            for(int i = 0; i < size_input; ++i){
                for(int j=0; j < size_input; j++){
                    sum += delta[b][f][i][j] * x_norm[b][f][i][j];
                }
            }
        }
        scale_updates[f] += sum;
    }
}


// 对方差求导
// 对应了论文中的求导公式2
void  compute_variance_delta(matrix x_matrix, matrix delta_matrix, vector<float> &mean, vector<float> &variance, int epislon, vector<float> &variance_delta)
{
    vector<vector<vector<vector<float>>>> &delta=delta_matrix.value;
    vector<vector<vector<vector<float>>>> &x=x_matrix.value;
    int batch_size=delta.size();
    int channel_input=delta[0].size(); // channel size
    int size_input=delta[0][0].size();

    for(int f = 0; f < channel_input; ++f){
        variance_delta[f] = 0;
        for(int b = 0; b < batch_size; ++b){
            for(int i = 0; i < size_input; ++i){
                for(int j=0; j < size_input; j++){
                    variance_delta[f] += delta[b][f][i][j]*(x[b][f][i][j] - mean[f]);
                }
            }
        }
        variance_delta[f] *= -.5 * pow(variance[f] + epislon, (float)(-3./2.));
    }
}

// 对均值求导
// 对应了论文中的求导公式3，不过Darknet特殊的点在于是先计算均值的梯度
// 这个时候方差是没有梯度的，所以公式3的后半部分为0，也就只保留了公式3的前半部分
// 不过我从理论上无法解释这种操作会带来什么影响，但从目标检测来看应该是没有影响的
//delta是l关于x_mao的损失
void compute_mean_delta(matrix &delta_matrix, matrix &x_matrix, vector<float> &mean, vector<float> &variance,  vector<float> &variance_delta, int epsilon, vector<float> mean_delta)
{
    vector<vector<vector<vector<float>>>> &delta=delta_matrix.value;
    vector<vector<vector<vector<float>>>> &x=x_matrix.value;
    int batch_size=delta.size();
    int channel_input=delta[0].size(); // channel size
    int size_input=delta[0][0].size();
     int base= size_input * size_input * batch_size;

    for(int f = 0; f < channel_input; ++f){
        mean_delta[f] = 0;
        for(int b = 0; b < batch_size; ++b){
            for(int i = 0; i < size_input; ++i){
                for(int j=0; j < size_input; j++){
                    mean_delta[f] += delta[b][f][i][j]; //不同batch, 同一channel的所有位置数据的损失加起来
                }
            }
        }
        mean_delta[f] *= (-1./sqrt(variance[f] + epsilon));
    }

    //还少了与variance_delta的那部分，及得添加上
    for(int f = 0; f < channel_input; ++f){
        int sum=0;
        for(int b = 0; b < batch_size; ++b){
            for(int i = 0; i < size_input; ++i){
                for(int j=0; j < size_input; j++){
                   sum+=(x[b][f][i][j]-mean[f]);
                }
            }
        }
        mean_delta[f] += variance_delta[f] * (-2.0) * sum / base;
    }

}

// 求出BN层的梯度敏感度图
// 对应了论文中的求导公式4，即是对x_i求导
void normalize_delta(matrix x_matrix, vector<float> &mean, vector<float> &variance, vector<float>&mean_delta, vector<float> &variance_delta, int epislon, matrix &delta_matrix)
{

    vector<vector<vector<vector<float>>>> &delta=delta_matrix.value;
    vector<vector<vector<vector<float>>>> &x=x_matrix.value;
    int batch_size=delta.size();
    int channel_input=delta[0].size(); // channel size
    int size_input=delta[0][0].size();

    int base= size_input * size_input * batch_size;
    for(int f = 0; f < channel_input; ++f){
        for(int b = 0; b < batch_size; ++b){
            for(int i = 0; i < size_input; ++i){
                for(int j=0; j < size_input; j++){
                    delta[f][b][i][j] = delta[f][b][i][j] * 1./(sqrt(variance[f] + epislon)) + variance_delta[f] * 2. * (x[f][b][i][j] - mean[f]) / base + mean_delta[f]/base;
                }
            }
        }
    }
}
//batch_normalization的倒数
// y_matrix其实就是x_morm_matrix 也就是bn的输出， x_matrix就是bn的输入， delata_matrix是上一层传过来的delta
// bn需要保留的参数除了输出激活，还有var, mean, gamma, beta, epislon
void BN::backward(matrix &x_matrix, matrix &y_matrix, matrix &delta_matrix){
    vector<vector<vector<vector<float>>>> &input=y_matrix.value; // 
    int batch_size=input.size();
    int channel_input=input[0].size(); // channel size
    int size_input=input[0][0].size();


    vector<float> scale_updates(channel_input);
    vector<float> variance_delta(channel_input);
    vector<float> mean_delta(channel_input);

    // matrix delta_matrix=matrix(batch_size, channel_input, size_input);

    vector<vector<vector<vector<float>>>> &res=delta_matrix.value;
    res.resize(batch_size);
    for (int i = 0; i < batch_size; ++i) {
        res[i].resize(channel_input);
        for (int j = 0; j < channel_input; ++j){
            res[i][j].resize(size_input);
            for(int k = 0;k < size_input; k++){
                res[i][j][k].resize(size_input);
            }
        }     
    }

    
    compute_backward_scale(y_matrix, delta_matrix, scale_updates);
    compute_variance_delta(x_matrix, delta_matrix, mean, variance, epislon, variance_delta);
    compute_mean_delta(delta_matrix, x_matrix, mean, variance, variance_delta, epislon, mean_delta);
    normalize_delta(x_matrix, mean, variance, mean_delta, variance_delta, epislon, delta_matrix);

} 

