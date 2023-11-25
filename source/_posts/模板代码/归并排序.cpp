class Solution {
public:
    int res=0;
    void merge(vector<int> &nums, int left, int mid, int right){
        
        int i=left, j=mid+1;
        //////// 其他计算逻辑//////
        while(i<=mid){
            while(j<=right&&(long long)nums[i]>(long long)2*nums[j]) j++;
            res+=(j-mid-1);
            i++;
        }

        /////////////////////////
        i=left, j=mid+1;
        vector<int> tmp(right-left+1, 0);
        int cur=0;
        while(i<=mid&&j<=right){
            if(nums[i]<=nums[j]){
                tmp[cur++]=nums[i++];
            }else{
                tmp[cur++]=nums[j++];
            }
        }
         
        while(i<=mid){
            tmp[cur++]=nums[i++];
        }
        while(j<=right){
            tmp[cur++]=nums[j++];
        }
        
        for(int i=left;i<=right;i++){
            nums[i]=tmp[i-left];
        }
    }
    void merge_sort(vector<int> &nums, int left, int right){
        if(left>=right){
            return;
        }
        int mid=left+(right-left)/2;
        merge_sort(nums, left, mid);
        merge_sort(nums, mid+1, right);
        merge(nums, left, mid, right);
    }
    int reversePairs(vector<int>& nums) {
        
        merge_sort(nums, 0, nums.size()-1);
        return res;
    }
};