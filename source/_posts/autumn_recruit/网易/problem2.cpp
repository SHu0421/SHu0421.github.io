#include<iostream>
#include<algorithm>
#include<math.h>
#include<string>
#include<vector>
using namespace std;

int main(){
    string s;
    cin>>s;
    int size=s.size();
    vector<int> r(size+1, 0);
    vector<int> e(size+1, 0);
    vector<int> d(size+1, 0);
    int res=0;
    for(int i=1;i<=size;i++){
        r[i]=r[i-1];
        e[i]=e[i-1];
        d[i]=d[i-1];
        if(s[i-1]=='r'){
            r[i]=r[i-1]+1;
        }else if(s[i-1]=='e'){
            e[i]=e[i-1]+1;
        }else{
            d[i]=d[i-1]+1;
        }
        for(int j=0;j<i;j++){
            if(r[i]-r[j]==e[i]-e[j]&&r[i]-r[j]==d[i]-d[j]){
                res++;
            }
        }
    }
    cout<<res<<endl;
    return 0;
}