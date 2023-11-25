



#include<iostream>
#include<vector>
#include<cmath>
#include "forward.h"
using namespace std;




class DNN{
    vector<layer*> layers;
    vector<matrix> out_activations;
    float loss;
	public:
		DNN(){};
		virtual ~DNN(){};

		void initNet(){
            //n_c, int out_c, int k_size,  int s, int p
             Conv *c=new Conv(3, 5, 2, 2, 0);
             layers.push_back(c);
             BN *b=new BN();
             layers.push_back(b);
             Relu *r=new Relu();
             layers.push_back(r);
        }

		// Initialise the weights matrices.
		// void initWeights(){
        //     for(int i=0;i<layers.size();i++){
        //         layers[i].initWeights();
        //     }
        // }

		// Forward
		void forward(matrix &input_matrix){
            cout<<"enter net forward function"<<endl;
            cout<<"layers.size():"<<layers.size()<<endl;
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
            // calloss()

        }

        // void backward(){
        //     deltaErr();
        //     updateWeights();
        // }
};



matrix getRandMatrix(int b, int c,  int m, int n){
    matrix res;
    res.value=vector<vector<vector<vector<float>>>>(b, vector<vector<vector<float>>>(c, vector<vector<float>>(m, vector<float>(n))));
    for(int i=0;i<b;i++){
        for(int j=0;j<c;j++){
            for(int k=0;k<m;k++){
                for(int q=0;q<n;q++){
                    res.value[i][j][k][q]=rand();
                }
            }
        }
    }
    return res;
}
int main(){
    DNN n;
    n.initNet();
    matrix input_matrix = getRandMatrix(1, 3, 4, 4);
    n.forward(input_matrix);
    cout<<"finish"<<endl;
    return 0;
}