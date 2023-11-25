#include<iostream>
#include<algorithm>
#include<math.h>
using namespace std;

double MySqrt(int val){
    double left=1, right = 23;
    // cout<<"hello world"<<endl;
    while(right-left>1e-12){
        double mid=(left+right)/2.0;
        if(mid*mid>val){
            right=mid;
        }else{
            left=mid;
        }
        // cout<<"hello world"<<endl;
        // printf("%.10f", left);
        // printf("%.10f", right);
    }
    return left;
}
int main(){
    long long res = (MySqrt(23)-4)*pow(10,10);
    cout<<res<<endl;
    // printf("%lld",res);
    return 0;
}