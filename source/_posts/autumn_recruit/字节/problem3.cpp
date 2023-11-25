#include<iostream>
#include<vector>
using namespace std;

bool compare(string pattern, string target){
    pattern=" "+pattern;
    target=" "+target;
    int size1=pattern.size();
    int size2=target.size();
    // cout<<pattern<<endl;
    // cout<<target<<endl;
    vector<vector<int> > dp(size1, vector<int>(size2, 0));
    dp[0][0]=1;
    for(int i=1;i<size1;i++){
        for(int j=1;j<size2;j++){
            if(pattern[i]!='*'){
                if(pattern[i]==target[j]){
                    dp[i][j]=dp[i-1][j-1];
                } 
            }else{
                dp[i][j]=dp[i][j-1]||dp[i-1][j]||dp[i-1][j-1];
            }
        }
    }
    return dp[size1-1][size2-1];
}
int main(){
   int n;
   scanf("%d", &n);
   char pattern[100];
    scanf("%s", pattern);
   string source;
   for(int i=0;pattern[i]!='\0';i++){
        if(pattern[i]!='{'){
            source+=pattern[i];
        }else{
            while(pattern[i]!='}'){
                i++;
            }
            source+='*';
        }
   }
   cout<<source<<endl;
   for(int i=0;i<n;i++){
        char target[100];
        scanf("%s", target);
        string b;
        for(int j=0;target[j]!='\0';j++){
            b+=target[j];
        }
        cout<<compare(source, b)<<endl;
   }
    return 0;
}