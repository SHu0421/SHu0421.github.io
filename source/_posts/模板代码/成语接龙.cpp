
//先words中两两结合，然后形成新的2*wordLen然后重复这样的过程，每次wordLen翻倍
struct node{
    string cur;
    int len;
};

vector<node> final;
void jieLongSub(vector<node> words)
{
    vector<node> res;

    for (int i = 0; i < words.size();i++){
        for (int j = 0; j < words.size(); j++){
            if(i!=j){
                if(canConnect(words[i], words[j])){
                    res.push_back(connect(words[i], words[j])); //如果不能和其他连接的节点就被舍弃掉了
                }
            }
        }
    }
    return res;
}

void jieLongMain(vector<node> words)
{
    vector<node> res=words;
    vector<node> pre;
    
    do{
        pre = res;
        res = jieLongSub(res);
    } while (res.size() > 1);

    return pre;
}



//第二种方法：求以每个成语开头的最长，然后取最大，求每个成语开头最长使用DFS感觉会超时

// 我记得同等长度的BFS
void jieLongMain(vector<node> words)
{
    queue<node> q;
    int size = words.size();
    for (int i = 0; i < size; i++)
    {
        q.push(words[i]);
    }
        while (!q.empty())
        {
            int size = q.size();
            vector<int> vis_list;
            vector<node> res;
            for (int i = 0; i < size; i++)
            {
                node cur = q.top();
                q.pop();
                bool flag = false;
                for (int j = 0; j < words.size(); j++)
                {
                    if (!vis[j] && canConnect(cur, words[i]))){
                        flag = true;
                        vis_list.push_back(j);
                        node tmp = connect(cur, words[i]);
                        q.push(tmp);
                }
            }
            if(!flag){
                res.push_back(cur);//这个单词不能再延长了
            }
            
        }
        //一个size遍历完了再标记vis
        for (int j = 0; j < vis_list.size();j++){
                vis[j] = true;
        }  
    }
    return res;
}
