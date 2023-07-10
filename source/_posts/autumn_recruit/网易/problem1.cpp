#include<iostream>
#include<vector>
#include<unordered_map> 
using namespace std;
int main(){
    int n;
    cout<<"hello world"<<endl;
    scanf("%d", &n);
    vector<int> arr(n+1, 0);
    unordered_map<int, int> num2index;
    unordered_map<int, int> index2num;
    for(int i=1;i<=n;i++){
        int tmp;
        scanf("%d", &tmp);
        arr[i]=tmp;
        num2index[arr[i]]=i;
        index2num[i]=arr[i];
    }
    vector<vector<int> > res;
    for(int i=1;i<=n;i++){
        while(index2num[i]!=i){
            int cur_num=index2num[i];
            int upper_num= cur_num+1, lower_num=cur_num-1;
            int upper_index= num2index[upper_num], lower_index=num2index[lower_num];
            if(cur_num<i){
                index2num[upper_index]=cur_num;
                index2num[i]=upper_num;
                num2index[upper_num]=i;
                num2index[cur_num]=upper_index;
                res.push_back({i, upper_index});
            }else{
               index2num[lower_index]=cur_num;
                index2num[i]=lower_num;
                num2index[lower_num]=i;
                num2index[cur_num]=lower_index;
                res.push_back({i, lower_index});
            }
            cout<<cur_num<<" "<<i<<endl;
        }
    }
    cout<<res.size()<<endl;
    for(int i=0;i<res.size();i++){
        cout<<res[i][0]<<" "<<res[i][1]<<endl;
    }
    return 0;
}