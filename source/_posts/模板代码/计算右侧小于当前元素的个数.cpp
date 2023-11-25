
// 方法一：归并排序
vector<int> res;
vector<int> index;
void merge(vector<int> &nums, int left1, int right1, int left2, int right2)
{
    int size = nums.size();
    vector<int> tmp(size, 0);
    int cur = left1;
    int mid = left2;
    while (left1 < right1 && left2 < right2)
    {
        if(nums[left1]<nums[left2]){
            tmp[cur] = nums[left1];
            res[index[left1]] += (left2 - mid);
            index[cur++] = index[left1++];
        }
        else if (nums[left1] >= nums[left2]) //稳定性
        {
            tmp[cur] = nums[left2];
            index[cur++] = index[left2++];
        }
    }

    while(left1<right1){
        tmp[cur] = nums[left1];
        res[index[left1]] += (left2 - mid);
        index[cur++] = index[left1++];
    }

    while(left2<right2){
        tmp[cur] = nums[left2];
        index[cur++] = index[left2++];
    }

    for (int i = left1;i<right2){
        nums[i] = tmp[i];
    }
}

void mergeSort(vector<int>& nums, int left, int right){
    if(left>=right){
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(nums, left, mid);
    mergeSort(nums, mid+1, right);
    merge(left, mid, mid + 1, right);
}

vector<int> countSmaller(vector<int>& nums) {
    int size = nums.size();
    res = vector<int>(size, 0);
    index = vector<int>(size, 0);
    for (int i = 0; i < size;i++){
        index[i] = i;
    }
    mergeSort(nums, 0, size);
    return res;
}


//官方代码
class Solution {
public:
    vector<int> index;//用于解决排序后原数组元素顺序变更问题

    void merge(vector<int> &nums,int left,int mid,int right,vector<int> &res)
    {
        int n=right-left+1;
        int *tmp=new int[n],*tempIndex=new int[n];
        int tmpPos=0;
        int leftPos=left,rightPos=mid+1;
        while(leftPos<=mid && rightPos<=right)
        {
            if(nums[leftPos]>nums[rightPos])//数组降序排列
            {
                res[index[leftPos]]+=right-rightPos+1;//用下标直接计算排序好的右半部分小于nums[leftPos]元素的数目
                tempIndex[tmpPos]=index[leftPos];//记录元素位置的改变，与排序思想相同
                tmp[tmpPos++]=nums[leftPos++];
            }
            else//nums[leftPos]<=nums[rightPos]，等号放在这里是为了更方便上面计算right-rightPos+1这个数目
            {
                tempIndex[tmpPos]=index[rightPos];//记录元素位置的改变，与排序思想相同
                tmp[tmpPos++]=nums[rightPos++];
            }
        }
        while(leftPos<=mid)
        {
            tempIndex[tmpPos]=index[leftPos];
            tmp[tmpPos++]=nums[leftPos++];
        }
            
        while(rightPos<=right)
        {
            tempIndex[tmpPos]=index[rightPos];
            tmp[tmpPos++]=nums[rightPos++];
        }
            
        for(int i=0;i<n;++i)
        {
            nums[left+i]=tmp[i];
            index[left+i]=tempIndex[i];
        }
        delete[] tmp;
        delete[] tempIndex;
    }
    void mergesort(vector<int> &nums,int left,int right,vector<int> &res)
    {
        if(left==right) return;
        int mid=(right-left)/2+left;
        mergesort(nums,left,mid,res);
        mergesort(nums,mid+1,right,res);
        merge(nums,left,mid,right,res);
    }
    vector<int> countSmaller(vector<int>& nums) {
        vector<int> res(nums.size(),0);
        index.resize(nums.size());
        for(int i=0;i<nums.size();++i) index[i]=i;
        mergesort(nums,0,nums.size()-1,res);
        return res;
    }
};



//方法二： 树状数组

    int arr[20002];
    
    int lowbit(int i){
        return i&(-i);
    }
    int getSum(int index){
        int sum=0;
        for(int i=index-1;i>0;i-=lowbit(i)){
            sum+=arr[i];
        }
        return sum;
    }

    void update(int index){
        for(int i=index;i<=20001;i+=lowbit(i)){
            arr[i]+=1;
        }

    }
    vector<int> countSmaller(vector<int>& nums) {
        memset(arr, 0,sizeof(arr));
        int size=nums.size();
        vector<int> res;
      

        for(int i=size-1;i>=0;i--){
            int ans = getSum(nums[i]+10000+1);
            res.push_back(ans);
            update(nums[i]+10000+1); 
        }
        reverse(res.begin(), res.end());
        return res;
    }
