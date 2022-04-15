// lc95. Unique Binary Search Trees II

#include<vector>
#include<iostream>
#include<stack>
#include<unordered_map>
using namespace std;
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

    vector<TreeNode*> generateTrees(int left, int right){
        if(left==right){
            TreeNode* tmp=new TreeNode(left);
            return {tmp};
        }
        if(left>right){
            return {NULL};
        }
        vector<TreeNode*> ans;
        for(int i=left;i<=right;i++){
            vector<TreeNode*> left_trees=generateTrees(left, i-1); 
            vector<TreeNode*> right_trees=generateTrees(i+1, right);
            for(int j=0;j<left_trees.size();j++){
                for(int k=0;k<right_trees.size();k++){
                    TreeNode* tmp=new TreeNode(i);
                    tmp->left=left_trees[j];
                    tmp->right=right_trees[k];
                    ans.push_back(tmp);
                }
            } 
        }
        return ans;
    }
    vector<TreeNode*> generateTrees(int n) {
        if(n==0){
            return {};
        }
        vector<TreeNode*> res = generateTrees(1, n);
        return res;
    }


 //如果是二叉树搜索树就是

for(int i=left;i<=right;i++){
    vector<vector<int>> left_trees=generateTrees(left+1, i); 
    vector<vector<int>> right_trees=generateTrees(i+1, right);
    for(int j=0;j<left_trees.size();j++){
        for(int k=0;k<right_trees.size();k++){

            vector<vector<int>> tmp;
            for (int m = 0; m < left_trees[i].size();m++){
                tmp.push_back(left_trees[i][m]);
            }
                tmp.push_back(left);
            for (int n = 0; n < right_trees[j].size();n++){
                tmp.push_back(right_trees[j][n]);
            } 
                ans.push_back(tmp);
        }
    } 
}


