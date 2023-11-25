#include<iostream>
using namespace std;
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n, k;
        scanf("%d%d", &n, &k);
        string s;
        scanf("%s", &s);
        int i=s.size()-1;
        while(i>=0&&s[i]!=0){
            i--;
        }//找到第一个0
        int j=i-1;
        while(j>=0&&s[j]!=1){
            j--;
        }
        if()
        
        
    }
    
    cout<<"hello world"<<endl;
    return 0;
}