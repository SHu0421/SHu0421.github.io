#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include "forward.h"
using namespace std;

struct matrix{
    vector<vector<vector<vector<float>>>> value;
    matrix(){};
    ~matrix(){};
    void randInitValue(int b, int c, int s){
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
    matrix(int b, int c, int s){
       value = vector<vector<vector<vector<float>>>>(b, vector<vector<vector<float>>>(c, vector<vector<float>>(s, vector<float>(s))));
       randInitValue(b, c, s);
    };
    
};

    

class layer{
    public:
    string type;
    layer(){};
    virtual ~layer(){};
    virtual void forward(matrix &input_matrix, matrix &output_matrix){
        cout<<"enter father layer forward function"<<endl;
    };
};

class Conv: public layer{
    public:
    int in_channel,  out_channel,  kernel_size,   stride,  padding;
    matrix w_matrix;
    vector<float> bias;

    Conv(){
        type="conv";
    };
   virtual  ~Conv(){};
    Conv(int in_c, int out_c, int k_size,  int s, int p){
        w_matrix =  matrix(out_c, in_c, k_size);
        type="conv";
        in_channel=in_c;
        out_channel=out_c;
        kernel_size=k_size;
        stride=s;
        padding=p; //加在输入，不是weight上

        bias=vector<float>(out_c);
        
    }
    //计算一个卷积核
    float computeOneKernel(vector<vector<vector<float>>> &input, vector<vector<vector<float>>> &weight, int m, int n, 
        int channel, int in_size, int w_size, int stride, int padding){
        float ans=0;
        for(int k=0;k<channel;k++){
            for(int i=0;i<w_size;i++){
                for(int j=0;j<w_size;j++){
                    if(m*stride+i-padding>=0&&n*stride+j-padding>=0&&m*stride+i-padding<in_size&&n*stride+j-padding<in_size){
                        // cout<<k<<" "<<m*stride+i-padding<<" "<<n*stride+j-padding<<endl;
                        ans+=input[k][m*stride+i-padding][n*stride+j-padding]*weight[k][i][j];
                    }
                }
            } 
        }
        return ans;
    }
    void forward(matrix &input_matrix, matrix &output_matrix){
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
                        float oneNum = computeOneKernel(input[batch], weight[num],  m, n,  in_c, in_size, w_size, stride, padding);
                        // cout<<oneNum<<endl;
                        res[batch][num][m][n]= oneNum + bias[num];
                    }
                }
            }
        }
        cout<<"return from conv layer"<<endl;

    }
};

class BN: public layer{
    public:
    float gamma;
    float beta;
    float epislon;
    vector<float> mean;
    vector<float> stdvar;
    BN(){
        type="bn";
        gamma=1;
        beta=0;
        epislon=0.0000001;
    };
    virtual ~BN(){};
    BN(float g, float b, float e){
        type="bn";
        gamma=g;
        beta=b;
        epislon=e;
    }
    void initWeight();
    
    void forward(matrix &input_matrix, matrix &output_matrix){
         vector<vector<vector<vector<float>>>> &input=input_matrix.value;
        int batch_size=input.size();
        int channel_size=input[0].size(); 
        int m_size=input[0][0].size();

        mean=vector<float>(channel_size, 0);
        stdvar=vector<float>(channel_size, 0);

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
                        stdvar[i]+=(input[b][i][j][k]-mean[i])*(input[b][i][j][k]-mean[i]);
                    }
                }
            }
            stdvar[i]=sqrt(stdvar[i]/(batch_size*m_size*m_size)+epislon);
        }

        for(int i=0;i<channel_size;i++){
            for(int j=0;j<m_size;j++){
                for(int k=0;k<m_size;k++){
                    for(int b=0;b<batch_size;b++){
                        res[b][i][j][k]=(input[b][i][j][k]-mean[i])/stdvar[i];
                    }
                }
            }
        }

    }
};

class Relu: public layer{
    public:
    Relu(){
        type="relu";
    };
    virtual ~Relu(){};
    void forward(matrix &input_matrix, matrix &output_matrix){
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
                        if(input[b][i][j][k]>0){
                            res[b][i][j][k]=1;
                        }
                    }
                }
            }
        }
    }
};
