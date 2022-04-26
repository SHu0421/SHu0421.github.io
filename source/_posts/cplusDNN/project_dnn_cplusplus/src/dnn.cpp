
#include<iostream>
#include<vector>
#include<cmath>
#include "base_layer.h"
#include "conv_layer.h"
#include "bn_layer.h"
#include "relu_layer.h"
#include "conv_bn_relu.h"
#include "dnn.h"
using namespace std;



DNN::DNN(){
    fuse=false; //在推理的时候设置fuse=true;
};
DNN:: ~DNN(){};

void DNN::initNet(){
        Conv *c=new Conv(3, 5, 2, 2, 0);
        layers.push_back(c);
        BN *b=new BN(1, 0, 0.00001, 5);
        layers.push_back(b);
        Relu *r=new Relu();
        layers.push_back(r);
}



// Forward
void DNN::forward(matrix &input_matrix){
    cout<<"enter net forward function"<<endl;
    cout<<"layers.size():"<<layers.size()<<endl;
    if(!fuse){
        for(int i=0;i<layers.size();i++){
            layer* l=layers[i];
            matrix out_matrix; 
            if(l->type=="conv"){
                    dynamic_cast<Conv*>(l)->forward(input_matrix, out_matrix);
            }else if(l->type=="bn"){
                    dynamic_cast<BN*>(l)->forward(input_matrix, out_matrix);
            }else if(l->type=="relu"){
                    dynamic_cast<Relu*>(l)->forward(input_matrix, out_matrix);
            }
            
            out_activations.push_back(out_matrix);
            input_matrix=out_matrix;
        }
    }else{
        for(int i=0;i<layers.size();){
            layer* l=layers[i];
            matrix out_matrix; 
            if(l->type=="conv"){
                BN* bn_l=dynamic_cast<BN*>(layers[i+1]);
                Conv* cur=dynamic_cast<Conv*>(l);
                Conv_BN_Relu* Conv_BN_Relu_obj=new Conv_BN_Relu(cur);

                Conv_BN_Relu_obj->forward_fusion(input_matrix, out_matrix, bn_l->mean, bn_l->variance,  bn_l->epislon, bn_l->gamma, bn_l->beta);
                i+=3;
            }
            
            out_activations.push_back(out_matrix);
            input_matrix=out_matrix;
        }
    }

    // calloss()
}

// void backward(){
//     deltaErr();
//     updateWeights();
// }



