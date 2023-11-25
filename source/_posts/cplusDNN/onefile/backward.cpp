#include<iostream>
#include<vector>
#include<algorithm>
#include<math>
#include "forward.cpp"

using namespace std;


//激活函数的倒数
void relu_back(matrix &input_matrix, matrix &output_matrix){
    vector<vector<vector<vector<float>>>> &input=input_matrix.value;
    int batch_size=input.size();
    int hei_input=input[0].size(); // channel size
    int size_input=input[0][0].size();
    // output_matrix的初始化在调用这个函数那一层
    // vector<vector<vector<vector<float>>>> dx(batch_size, vector<vector<vector<float>>>(hei_input, vector<vector<float>>(size_input, vector<float>(size_input, 0))));
    vector<vector<vector<vector<float>>>> &dx=output_matrix.value;

    for(int b=0;b<batch_size;b++){
        for(int i=0;i<hei_input;i++){
            for(int j=0;j<size_input;j++){
                for(int k=0;k<size_input;k++){
                    if(input[b][i][j][k]>0){
                        dx[b][i][j][k]=1;
                    }
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
void backward_scale(matrix &x_norm_matrix, matrix &delta_matrix, vector<float> &scale_updates)
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
void  variance_delta(matrix x_matrix, matrix delta_matrix, vector<float> &mean, vector<float> &variance, int epislon, vector<float> &variance_delta)
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
void mean_delta(matrix &delta_matrix, matrix &x_matrix, vector<float> &variance,  vector<float> &variance_delta, int epsilon, vector<float> mean_delta)
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
void normalize_delta(matrix x_matrix, vector<float> &mean, vector<float> &variance, vector<float>&mean_delta, vector<float> &variance_delta, int episolon, matrix &delta_matrix)
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
// x_norm_matrix其实就是bn的输出， x_matrix就是bn的输入， delata_matrix是上一层传过来的delta
// bn需要保留的参数除了输出激活，还有var, mean, gamma, beta, epislon
matrix bn_back(matrix &x_norm_matrix,  matrix &x_matrix, matrix &delta_matrix,  vector<float> &mean, vector<float> &variance, int epislon){
    vector<vector<vector<vector<float>>>> &input=x_norm_matrix.value;
    int batch_size=input.size();
    int channel_input=input[0].size(); // channel size
    int size_input=input[0][0].size();


    vector<float> scale_updates(channel_input);
    vector<float> variance_delta(channel_input);
    vector<float> mean_delta(batch_size, channel_input, size_input);
    matrix delta_matrix(channel_input);

    
    backward_scale(x_norm_matrix, delta_matrix, scale_updates);
    variance_delta(x_matrix, delta_matrix, mean,  variance, epislon, variance_delta);
    mean_delta(delta_matrix, x_matrix, variance,  variance_delta, epsilon, mean_delta);
    normalize_delta(x_matrix, mean, variance, mean_delta, variance_delta, episolon, delta_matrix);

} 
//batch_normalization的倒数
matrix conv_back(matrix &input_matrix){

}