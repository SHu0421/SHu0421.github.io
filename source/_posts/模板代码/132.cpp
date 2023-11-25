
#include<vector>

using namespace std;
class Solution
{
public:
    bool find132pattern(vector<int>& nums) {
        //方法一
        // int size = nums.size();
        // if(size<3){
        //     return false;
        // }
        // multiset<int> right_nums;
        // for (int i = size - 1; i >= 1; i--)
        // {
        //     right_nums.insert(nums[i]);
        // }
        // int left_min = nums[0];
        
        // for (int i = 1; i < size-1; i++)
        // {
        //     right_nums.erase(right_nums.find(nums[i]));
        //     auto iter = right_nums.upper_bound(left_min);
        //     if(iter!=right_nums.end()&&*iter<nums[i]){
        //         return true;
        //     }
        //     left_min = min(left_min, nums[i]);
        // }
        // return false;
        int two = INT_MIN;
        int size = nums.size();
        stack<int> s;
        for (int i = size - 1; i >= 0; i--)
        {
            if(nums[i]<two){
                return true;
            }
            while(!s.empty()&&nums[i]>s.top()){ //找到小于他的最大值
                two = s.top();
                s.pop();
            }
            s.push_back(nums[i]);
        }
        return false;
    }
};