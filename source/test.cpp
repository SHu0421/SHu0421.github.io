
// 计算每个元素的出现的个数

// 输入文件：（10亿，已经根据$1进行排序）
// a 5
// a 3
// b 3
// b 4
// c 5
// 输出：
// a 8
// b 7
// c 5

#include<iostream>
using namespace std;

unordered_map<string ,int> computeTimes(string filename){
    File* p=fopen(filename);
    string start;
    int cur_num;
    while(!endFile){
        string line = p.readLine();
        vector<string> results = line.split(" ");
        if(results[0]!=start){
            if(start!=""){
                cout<<start<<" "<<cur_num<<endl;
            }
            cur_num=results[1];
            start=results[0];
        }else{
            cur_num+=stoi(results[1]);
        }
    }
    cout<<start<<" "<<cur_num<<endl;

    /*unordered_map<string ,int> hash;
    while(!endFile){
        string line = p.readLine();
        vector<string> results = line.split(" ");
        hash[results[0]]+=stoi(results[1]);
    }
    return hash;*/
}

int main(){
    string filename="C://test.txt";
    unordered_map<string ,int> res = computeTimes(filename);
    return 0;
}


//////////////////////////////

import numpy as np 

class Sigmoid(object): 
    def __init__(self): 
        pass 
   
    def forward(self, x): 
        """ 
            input: x [ batch_size, in_dim ] 

            output: y [batch_size, in_dim ] 
        """

        return 1/(1+np.exp(-x));

   
   
    def backward(self, x, grad_y): 
         """ 
            input: x [ batch_size, in_dim ] 
            input: grad_y [ batch_size, in_dim ] 

            output: grad_x [batch_size, in_dim ] 
        """ 
        return grad_y*(1/(1+np.exp(-x)))*(1-1/(1+np.exp(-x)));



