#include<iostream>
#include<unordered_map>
#include<vector>
using namespace std;
int main(){
    int n;
    scanf("%d", &n);
    vector<int> preside(n, 0);
    unordered_map<int, int> prenum;
    unordered_map<int, int> totalnum;
    int num;
    for(int i=0;i<n;i++){
        scanf("%d", &num);
        preside[i]=num;
        prenum[num]++;
        totalnum[num]++;
    }
    for(int i=0;i<n;i++){
        scanf("%d", &num);
        if(preside[i]!=num){
            totalnum[num]++;
        }
    }
    int res=n;
    bool flag=false;
    for(auto iter=totalnum.begin(); iter!=totalnum.end(); iter++){
        if(iter->second>=n/2){
            res=min(res, n/2-prenum[iter->first]);
            flag=true;
        }  
    }
    if(flag){
        cout<<res<<endl;
    }else{
        cout<<-1<<endl;
    }
    
    

}