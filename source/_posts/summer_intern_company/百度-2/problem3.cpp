#include<iostream>
#include<vector>
#include<string>
using namespace std;


int gcd(int a, int b){
    if(b==0){
        return a;
    }
    return gcd(b, a % b);
}

int main(){
    int a=
    gcd(a, b);
    return 0;
}