#include<iostream>
#include<vector>
using namespace std;

//check whether the array with index from left to right is a BST
bool check(vector<int> &preorder, int left, int right, int min_num, int max_num){
    int index = preorder.size();
    if(left>right){
        return true;
    }
    if(left==right){
        return preorder[left] > min_num && preorder[left] < max_num;
    }
    for (int i = left+1; i < preorder.size(); i++)
    {
        if(preorder[i]>preorder[left]){
            index = i;
            break;
        }
    }
    if(preorder[left] > min_num && preorder[left] < max_num){ //judge whether the node value is within the range
        bool left_flag = check(preorder, left, index - 1, min_num, preorder[left]); // judge whether the left subtree is a BST/ call the function recursively
        bool right_flag = check(preorder, index, right, preorder[left], max_num);   // judge whether the right subtree is a BST
        return left_flag && right_flag;
    }
    return false;
}
string checkStructe(vector<int> &preorder)
{
    if(preorder.size()==0||preorder.size()==1){//judge the corner case
        return "YES";
    }
    if(check(preorder, 0, preorder.size()-1, INT_MIN, INT_MAX)){
        return "YES";
    }
    return "NO";
}