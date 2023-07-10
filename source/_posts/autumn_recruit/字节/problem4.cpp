#include<iostream>
#include<vector>
#include<map>
using namespace std;
void dfs(vector<int> arr, int index, int sum, float prob, map<int, float>& hash){
    int size=arr.size();
    if(index==size){
        hash[sum]+=prob;
        return;
    }
    for(int i=1;i<=arr[index];i++){
         dfs(arr, index+1, sum+i, prob*(1.0/arr[index]), hash);
    }
}
int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> arra(n, 0);
    vector<int> arrb(m, 0);
    map<int, float> hasha;
    map<int, float> hashb;
    for(int i=0;i<n;i++){
        scanf("%d", &arra[i]);
    }
    for(int i=0;i<m;i++){
        scanf("%d", &arrb[i]);
    }
    
    dfs(arra, 0, 0, 1, hasha);
    dfs(arrb, 0, 0, 1, hashb);
    auto iterb=hashb.begin();
    float sum=0.0;
    float res=0.0;
    for(auto itera=hasha.begin(); itera!=hasha.end(); itera++){
        // cout<<itera->first<<" "<<itera->second<<endl;
        for(; iterb!=hashb.end(); iterb++){
            if(itera->first<=iterb->first){
                break;
            }
            sum+=iterb->second;
            // cout<<iterb->first<<" "<<iterb->second<<endl;
        }
        res+=itera->second*sum;
    }
    printf("%.3f", res);
    return 0;
}