#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;

char getToken(long long pos, long long totalLen){
    string res1="MeiTuan";
    string res2="wow";
    if(pos>7){
        long long baseLen=(totalLen-3)/2;
        if(pos<=baseLen){
            return getToken(pos, baseLen);
        }else if(pos>baseLen&&pos<=2*baseLen){
            return getToken(2*baseLen-pos+1, baseLen);
        }else{
            return res2[totalLen-pos];
        }
    }
    return res1[pos-1];
}
int main(){
    int n;
    scanf("%d", &n);
    while(n--){
        long long pos;
        scanf("%lld", &pos);
        long long len=7;
        while(len<pos){
            len=len*2+3;
        }
        cout<<getToken(pos, len)<<endl;
    }
}