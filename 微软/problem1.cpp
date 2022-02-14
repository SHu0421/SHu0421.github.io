#include <iostream>
#include <vector>
using namespace std;


//主要思路：使用循环记录当前数的数量，如果数量比当前数的值还大，那么只能删除当前数的数量到当前值；
//如果数量比当前数小，那么可以删除数量到0， 也可以添加数到当前值，两者取最小
int solution(vector<int> &A) {
    // write your code in C++14 (g++ 6.2.0)
    int size=A.size();
    int res=0;
    while(i<size){
        int cur=A[i];
        int num=0;
        while(A[i]==cur){
            num++;
            i++;
        }
        if(num>=cur){
            res+=num-cur;
        }else{
            res+=min(cur-num, num);
        }
    }
    return res;
}