
#include<iostream>
#include "dnn.h"
#include "base_layer.h"
using namespace std;


int main(){
    DNN n;
    n.initNet();
    // n.fuse=true; // whether to use the Conv_BN_Relu fusion method
    matrix input_matrix(1, 3, 4, true);
    n.forward(input_matrix);
    cout<<"finish"<<endl;
    return 0;
}