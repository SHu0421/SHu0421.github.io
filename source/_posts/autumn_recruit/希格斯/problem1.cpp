// 超算集群中有 列表 job_list， 其元素为字符[A-Z]，每个字符代表一种不同种类的job。
// 每个job需要 1 的单位时间，但是在相邻两个同种job间，需要间隔至少 n 个单位时间。


// 给定 n 和 job_list，求完成所有job的最短时间。

// 1 <= len(job_list) <= 10^4
// 0 <= n <= 100


// job_list = ['E', 'S', 'E', 'S'], n=1
// output: 4

// job_list = ['E', 'S', 'E', 'S', 'E', 'S'], n=0
// output: 6

#include<iostream>
#include<vector>
#include<unordered_map>
#include<queue>
using namespace std;
struct node{
    char key;
    int time;
    int num;
    bool operator< (const node &a ) const{
        if(a.time!=this->time){
            return a.time <this->time;
        }
        return a.num > this->num;
    }
};


int findMinTime(vector<char> &job_list, int n)
{
    int size = job_list.size();
    unordered_map<char, int> hash;
    for (int i = 0; i < size; i++)
    {
        hash[job_list[i]]++;
    }
    // vector<node> node_list;
    priority_queue<node, vector<node> > q;
    for (auto iter = hash.begin(); iter != hash.end(); iter++)
    {
        node tmp ;
        tmp.key = iter->first;
        tmp.time = 1;
        tmp.num = iter->second;
        q.push(tmp);
    }
    int res = 0;
    while (!q.empty())
    {
        node now = q.top();
        q.pop();
        res = max(now.time, res+1);
        // cout << "now time:"<<res << endl;
        if (now.num != 1)
        {
            node new_node=now;
            new_node.time = res + n +1;
            new_node.num-=1;
            q.push(new_node);
        }
    }
    return res;
}

int main(){
    // vector<char> job_list = {'E', 'S','E', 'S', 'E', 'S'};
    // int n = 0;
    vector<char> job_list = {'E', 'S', 'E', 'S'};
    int n = 1;
    int res = findMinTime(job_list, n);
    cout << res << endl;
    return 0;
}
