// 本题为考试单行多行输入输出规范示例，无需提交，不计分。
#include <iostream>
#include <vector>
using namespace std;

float compute(int a, int b, int c){
    float left=-a/3.0;
    float right=0;
    float err=0.0000001;

    while(true){
        float mid=left+(right-left)/2.0;
        float sum=3*mid*mid+2*a*mid+b;
        cout<<left<<" "<<right<<" "<<mid<<endl;
        if(sum<err&&sum>-err){
            return mid;
        }else if(sum>0){
            right=mid;
        }else{
            left=mid;
        }
    }
    return -1;
}
int main() {
    int q;
    scanf("%d", &q);
    
    for(int i=0;i<q;i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        float res=compute(a, b, c);
        cout<<res<<endl;
    }
    return 0;
}