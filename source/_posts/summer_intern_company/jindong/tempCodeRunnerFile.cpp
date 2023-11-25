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
                res += (long long)(src / 3 + 1) * 3 - src;
                src = (long long )(src / 3 + 1) * 3;
            }else{
                src = (long long )src / 3;
                res += 1;
            }
        }
    }

    return res;
    // return 99;
}
int main(){
    int n;
    scanf("%d", &n);
    while (n)
    {
        long long src, target;
        scanf("%lld%lld", &src, &target);
        long long res = computeResult(src, target);
        printf("%lld", res);
        n--;
    }
    return 0;
}