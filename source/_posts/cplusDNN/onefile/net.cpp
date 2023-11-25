
// 1. The Convolution, BatchNorm and ReLU is a basic unit of CNN.
// In this test you need write the function of these three parts by C/C++(recommended, PLUS) or Python.

// Forward functions;
// Verify the results by test case
// PLUS: Backward functions
//  Select at least one of below two methods to improve performance 

// 2.PLUS: Analyze the computation efficiency (the ration of real computation FLOPS against theoretical FLOPS)


#include<iostream>
#include<vector>
#include<algorithm>
#include "forward.cpp"
using namespace std;

//一些参考资料：
// Darknet是使用C语言写的： https://github.com/pjreddie/darknet.git

//使用指针传参数另外一种实现方法：
//http://giantpandacv.com/academic/%E7%9B%AE%E6%A0%87%E6%A3%80%E6%B5%8B%E5%8F%8A%E8%B7%9F%E8%B8%AA/Darknet/%E5%9F%BA%E4%BA%8ECS231N%E5%92%8CDarknet%E8%A7%A3%E6%9E%90BatchNorm%E5%B1%82%E7%9A%84%E5%89%8D%E5%90%91%E5%92%8C%E5%8F%8D%E5%90%91%E4%BC%A0%E6%92%AD/


// https://zhuanlan.zhihu.com/p/61898234
// loss关于y的导数（上一层的x的导数）：原图的delta误差，等于卷积结果的delta误差经过零填充后，与卷积核旋转180度后的卷积
// 卷积中w的导数，二维卷积核的导数等于原图对应通道与卷积结果对应通道的delta误差直接进行卷积。
// b的导数(列向量)：在反向传播时，它的导数等于卷积结果的delta误差在每一个通道上将所有delta误差进行求和的结果。

//https://zhuanlan.zhihu.com/p/90301095 img2col and gemm



class Net{
    protected:
		vector<matrix> layer; //activation 值
		vector<matrix> weights; //权重值
		vector<matrix> bias; //bias值
        vector<matrix> deltaerr; //bias值
		float loss;

	public:
		Net(){};
		~Net(){};

		void initNet(vector<matrix> &input){
             
        }

		// Initialise the weights matrices.
		void initWeights();

		// Initialise the bias matrices.
		void initBias(bias);

		// Forward
		float forward(matrix &input){
            for(int i=0;i<weights.size();i++){
                matrix conv_res=conv_forward(input, weight[i]);
                matrix bn_res=bn_forward(conv_res);
                layer[i+1]=relu_forward(bn_res);
            }
            loss = compute_loss(layer[layer.size()-1], target);
        }

        void backward(){
            deltaErr();
            updateWeights();
        }
		// Forward
		void deltaErr(){
            for(int i=weights.size()-1;i>=0;i--){
                delta_err[i].create(layer[i + 1].size(), layer[i + 1].type());
             
                matrix dx_relu = relu_back(layer[layer.size()]-1); //激活函数的倒数

                matrix dx_bn = bn_back(layer[layer.size()]-1); //batch_normalization的倒数

                matrix dx_conv = conv_back(layer[layer.size()]-1); //batch_normalization的倒数

                //需要添加BN的倒数
                if(i==weights.size()-1){
                    delta_err[i] = dx.mul(output_error); //为什么不*-2
                }else // Hidden layer delta error
                {
                    matrix weight = weights[i];
                    matrix weight_t = rotate180(weight);
                    matrix delta_err_1 = delta_err[i];
                    delta_err[i] = conv_back(weight_t, delta_err[i+1]);
                }

                matrix conv_res=conv_forward(input, weight[i]);
                matrix bn_res=bn_forward(conv_res);
                layer[i+1]=relu_forward(bn_res);
            }
        }

        void updateWeights(){
            for (int i = 0; i < weights.size(); ++i)
            {
                matrix delta_weights = learning_rate * (delta_err[i] * layer[i].t()); //感觉还有一个激活函数输出关于输入的倒数在delta_error中已经实现了
                matrix delta_bias = learning_rate * delta_err[i];
                weights[i] = weights[i] + delta_weights;
                bias[i] = bias[i] + delta_bias;
            }
        }

}

