// 范围映射的树状数组

class Solution {
public:
  
    int res=0;
    vector<int> tree;
    int lowbit(int x){
        return x & (-x);
    }
    void update(int x){
        for (int i = x; i < tree.size();i+=lowbit(i)){
            tree[i] += 1;
        }
        
    }
    int query(int index){
        int res = 0;
        for (int i = index; i > 0; i -= lowbit(i))
        {
            res += tree[i];
        }
        return res;
    }
    int reversePairs(vector<int> &nums)
    {
        set<long long> s;
        for (int i = 0; i < nums.size(); i++)
        {
            s.insert(nums[i]);
            s.insert((long long)nums[i]*2);
        }
        int index = 1;
        unordered_map<long long, int> hash;
        // 范围映射的树状数组
        for (auto iter = s.begin(); iter != s.end(); iter++)
        {
            hash[*iter] = index++;
        }
        tree = vector<int>(index, 0);

        // cout<<index<<endl;
        for (int i = 0; i <nums.size(); i++)
        {
            int left = hash[(long long)nums[i]*2], right = index-1;
            // cout<<left<<" "<< right<<endl;
            res += query(right) - query(left);
            update(hash[nums[i]]);
        }

        return res;
    }
};