#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<unordered_map>
using namespace std;

int main(){
    int m,n,k;
    scanf("%d %d %d", &m, &n, &k);
    int MOD=pow(10,9)+7;
    if(k==1){
        cout<<m<<endl;
        return 0;
    }
    if(k==2){
        cout<<n<<endl;
        return 0;
    }
    long long a, b;
    a=m;
    b=n;
    long long cur;
    for(int i=3;i<=k;i++){
        cur=((((((m*n)%MOD)*m)%MOD)*n)%MOD);
        m=n;
        n=cur;
    }
   
    
    cout<<cur%MOD<<endl;
    return 0;
    
}