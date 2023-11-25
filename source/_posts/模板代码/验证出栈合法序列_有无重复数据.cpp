//验证合法的序列如果有重复


#include<vector>
#include<iostream>
#include<stack>
#include<unordered_map>
using namespace std;


unordered_map<int, int> my_hash;
bool dfs(int i, int j, stack<int> s, vector<int>& pushed, vector<int>& popped){
    int size = pushed.size();
    while (i < size && j < size)
    {
        s.push(pushed[i]);
        my_hash[pushed[i]]--;
        i++;
        while (j < size && !s.empty() && s.top() == popped[j])
        {
            if(my_hash[pushed[i]]==0){
                s.pop();
                j++;
            }else{
                if(dfs(i, j, s, pushed, popped)){ //遇到相同的后面如果还有元素，先不弹出去， 注意栈是复制不是引用
                    return true;
                }
                s.pop();
                j++;
            }
        }
    }
    return j == size;
}
bool validateStackSequencesDuplicated(vector<int>& pushed, vector<int>& popped) {
        int size=pushed.size();
        stack<int> s;

        for (int i = 0; i < size; i++)
        {
            my_hash[pushed[i]]++;
        }
        return dfs(0, 0, s, pushed, popped);
        
}


bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int size=pushed.size();
        stack<int> s;
        int i=0, j=0;
        while(i<size&&j<size){
            
            s.push(pushed[i++]);
            
            while(j<size&&!s.empty()&&s.top()==popped[j]){
                s.pop();
                j++;
            }
        }
        if(!s.empty()){
            return false;
        }
        return true;
    }



int main(){
    // vector<int> pushed = {1,2,7,2,3};
    // vector<int> popped = {2,3,7,2,1};

    vector<int> pushed = {1,4,3,4,5};
    vector<int> popped = {4,5,3,4,1};
    bool flag = validateStackSequencesDuplicated(pushed, popped);
    bool flag_error = validateStackSequences(pushed, popped);
    cout << flag << endl;
    cout << flag_error << endl;
    return 0;
}
