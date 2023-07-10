#include<string>
#include<vector>

using namespace std;
int findnext(string s)
{
    int size = s.size();
    int k = -1;
    vector<int> next(size, -1);
    next[0] = -1;
    for (int i = 1; i < size; i++)
    {
        while (k != -1&&s[k+1] != s[i])
        {
            k = next[k];
        }

        if(s[i]==s[k+1]){
            k++;
        }

        next[i] = k;
    }
    return next[size-1]+1; //next对应的是相等的下标，长度应该+1
}