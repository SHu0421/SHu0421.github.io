class LoadBalancer {
public:
    vector<int>v;
    unordered_map<int,int>m;

    LoadBalancer() {
        // do intialization if necessary
        srand(time(NULL));
    }

    /*
     * @param server_id: add a new server to the cluster
     * @return: nothing
     */
    void add(int server_id) {
        // write your code here
        m[server_id] = v.size();
        v.push_back(server_id);
    }

    /*
     * @param server_id: server_id remove a bad server from the cluster
     * @return: nothing
     */
    void remove(int server_id) {
        // write your code here
        int pos = m[server_id];
        m.erase(m.find(server_id));
        swap(v[pos],v[v.size()-1]);
        m[v[pos]]=pos;
        v.pop_back();
    }

    /*
     * @return: pick a server in the cluster randomly with equal probability
     */
    int pick() {
        // write your code here
        return v[rand()%v.size()];
    }
};



class Solution {
public:
    struct node{
        int data;
        int time;
    };
    int minimumOperations(vector<int>& nums) {
        int size=nums.size();
        unordered_map<int, int> hash;
        int max_cnt=0;
        int max_data=-1;
        int second_cnt=0;
        int max_cnt_2=0;
        int max_data_2=-1;
        int second_cnt_2=0;
        int res=0;
        for(int i=0;i<size;i+=2){
            hash[nums[i]]++;
            if(hash[nums[i]]>=max_cnt){
                if(nums[i]!=max_data){
                    second_cnt=max_cnt;
                }
                max_cnt=hash[nums[i]];
                max_data=nums[i];
                
            }
        }
        hash.clear();
        for(int i=1;i<size;i+=2){
            hash[nums[i]]++;
            if(hash[nums[i]]>=max_cnt_2){
                if(nums[i]!=max_data_2){
                    second_cnt_2=max_cnt_2;
                }
                max_cnt_2=hash[nums[i]];
                max_data_2=nums[i];
                
            }
        }
        // cout<<max_data<<" "<<max_cnt<<" "<<second_cnt<<endl;
        // cout<<max_data_2<<" "<<max_cnt_2<<" "<<second_cnt_2<<endl;
        if(max_data!=max_data_2){
            return size-max_cnt-max_cnt_2;
        }else{
            if(second_cnt>second_cnt_2){
                return size-second_cnt-max_cnt_2;
            }else{
                // cout<<max_cnt<<" "<<second_cnt_2<<endl;
                return size-max_cnt-second_cnt_2;
            }
        }
        
        
    }
};



//鸡蛋掉落问题
dp[i][j] 确定的最高

dp[1][i] = 1;
int i = 2;
while (true)
{
    for (int j = 1; j <= k;j++){
        dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1] + 1;
    }
    if(dp[i][k]>=n){
        return i;
    }
    else{
        i++;
    }
}


    
