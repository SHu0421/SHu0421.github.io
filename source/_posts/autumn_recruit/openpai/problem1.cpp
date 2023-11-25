
#include<iostream>
#include<vector>
using namespace std;
vector<vector<int>> res;
void dfs(int index, vector<int> &nums){
  int size=nums.size();
  if(index==size){
    res.push_back(nums);
  }
  for(int i=index;i<size;i++){
    if(i>index&&nums[i]==nums[i-1]){
      continue;
    }
    swap(nums[index], nums[i]);
    dfs(index+1, nums);
    swap(nums[index], nums[i]);
  }
}
vector<vector<int>> findAllPermutation(vector<int> &nums){
  sort(nums.begin(), nums.end());
  dfs(0, nums);
  return res;
}

int main(){
  vector<int> nums={1, 1, 2};
  findAllPermutation(nums);
  int size=res.size();
  int len=nums.size();
  for(int i=0;i<size;i++){
    for(int j=0;j<len;j++){
      cout<<res[i][j]<<" ";
    }
    cout<<endl;
  }
  return 0;
}