#include<iostream>
#include<vector>
#include<string>
using namespace std;

int computeResult(long long src, long long target){
    long long res = 0;
    while(src!=target){
        if(src<target){
            res += target - src;
            res = target;
            break;
        }
        else
        {
            if(src%3!=0){
                res += (long long)(3-src%3);
                src += (long long)(3-src%3) ;
            }else{
                if(src<=3*target){}
                src = min(computeResult(src + 1, target) + 1, computeResult(src/3, target) + 1);
            }
        }
    }

    return res;
}
int main(){
    int n;
    scanf("%d", &n);
    while (n)
    {
        long long src, target;
        scanf("%lld%lld", &src, &target);
        long long res = computeResult(src, target);
        printf("%d", res);
        n--;
    }
    return 0;
}