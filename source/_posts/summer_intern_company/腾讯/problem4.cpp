
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     * 你需要返回m个指针，每个指针指向一条链，表示树上的一条链。
     * @param root TreeNode类 表示题目给出的树;
     * @param b int整型vector<vector<>> 第二维给出4个值，依次表示x,y,u,v;
     * @return ListNode类vector
     */
    unordered_map<TreeNode*, TreeNode*> father;
    unordered_map<int, TreeNode*> val2node;
    void dfs(TreeNode *root){
        if(root==NULL){
            return;
        }
        val2node[root->val]=root;
        if(root->left){
            father[root->left]=root;
            dfs(root->left);
        }
        if(root->right){
            father[root->right]=root;
            dfs(root->right);
        }
    }
    bool find(TreeNode* cur, TreeNode* target, unordered_map<int, bool> vis){
        vis[cur->val]=true;
        if(cur==target){
            return true;
        }
        if(cur->left){
            
            if(find(cur->left,target, vis){
                return true;
            }
        }
        if(cur->right){
            if(find(cur->right,target, vis){
                return true;
            }
        }
        if(!vis[father[cur]->val]){
            if(find(father[cur],target, vis){
                return true;
            }
        }

        vis[cur->val]=false;
    }

    bool find2(TreeNode* cur, TreeNode* target, unordered_map<int, bool> &mark, unordered_map<int, bool> &vis, vector<int> &res){
        if(cur==NULL){
            return;
        }
        vis[cur->val]=true;
        if(mark[cur->val]){
            res.push_back(cur->val);
        }
        if(cur==target){
            return true;
        }
        if(cur->left){
            if(find(cur->left,target, vis){
                return true;
            }
        }
        if(cur->right){
            if(find(cur->right,target, vis){
                return true;
            }
        }

        if(!vis[father[cur]->val]){
            if(find(father[cur],target, vis){
                return true;
            }
        }
        vis[cur->val]=false;
        if(mark[cur->val]){
            res.pop_back();
        }
    }

    vector<ListNode*> buildList(vector<int> res){
        ListNode * head;
        ListNode * cur=head;
        for(int i=0;i<res.size();i++){
            ListNode * tmp;
            tmp->val=res[i];
            cur->next=tmp;
            cur=tmp;
        }
        return head->next;
    }
    vector<ListNode*> solve(TreeNode* root, vector<vector<int> >& b) {
        // write code here
        dfs(root);
        vector<TreeNode*> ans;
        for(int i=0;i<b.size();i++){
            unordered_map<int, bool> mark;
            vector<int> res;
            find1(val2node[b[i][0]],val2node[b[i][1]], mark);
            unordered_map<int, bool> vis;
            find2(val2node[b[i][2]], val2node[b[i][3]], mark, vis,res);
            if(res.size()>0){
                if(res.size()>1&&res[res.size()-1]<res[0]){
                    reverse(res.begin(), res.end());
                }
                ans.push_back(buildList(res));
                
            }else{
                ans.push_back(NULL);
            }
        }
        
    }
};