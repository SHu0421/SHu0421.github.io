#include<iostream>
#include<vector>
using namespace std;

float power(float a, int b){
    float base = a;
    float res = 1.0;
    bool neg = b < 0 ? 1 : 0;
    b = abs(b);
    while (b)
    {
        if(b&1){ // 101
            res = res * base;
        }
        b = b >> 1;
        base = base * base; 
    }
    if(neg){
        // cout << res << " "<<1.0 / res << endl;
        return (float)(1.0 / res);
    }

    return res;
}

int main(){
    float a = 0.5;
    int b = -8;

    float res = power(a, b);

    cout << res << endl;
    return 0;
}