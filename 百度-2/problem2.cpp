#include<iostream>
#include<vector>
#include<string>
using namespace std;


//解为num1+num2最大
//满足x*num1+y*num2<=a
//满足x*num2+y*num1<=b
long long res = 0;
// void findMax(long long a, long long b, long long x, long long y)
// {
//     for (int num1 = 0; num1 <= a / x; num1++)
//     {
//         for (int num2 = 0; num2 <= a / y;num2++){
//             if((long long)x*num1+y*num2<=a&&(long long)x*num2+y*num1<=b){
//                 if(res<(num1+num2)){
//                     res = num1 + num2;
//                 }
//             }
//         }
//     }
// }
void findMax2(long long a, long long b, long long x, long long y)
{
    long long left = 0, right = max(a / y, b/x);
    if(x==y){
        res = min(a / x, b / y);
        return;
    }
    while(left<=right){
        long long mid = left + (right - left) / 2;
        long long tmp1=(a+(x-y)*mid)/x;
        long long tmp2 = (b + (y - x) * mid) / y;
        if(tmp1==tmp2){
            res = tmp1;
            return;
        }
        if(tmp1>tmp2){
            if(x>y){
                right = mid - 1;
            }else{
                left = mid + 1;
            }
        }else{
            if(x>y){
                left = mid + 1;
            }else{
                right = mid - 1;
            }
        }
    }
    res = max(min((a + (x - y) * left) / x, (b + (y - x) * left) / y), min((a + (x - y) * right) / x, (b + (y - x) * right) / y));
}

int main(){

    long long a, b, x, y;
    scanf("%lld%lld%lld%lld", &a, &b, &x, &y);
    findMax2(a, b, x, y);
    cout << res << endl;
    return 0;
}