#include<iostream>

using namespace std;

int main(){
  int n;
  scanf("%d",&n);
  long long left=1, right=1;
  long long cur=0;
  printf("[");
  bool first=true;
  while(right<n){
    cur+=right;
    while(cur>n){
        // cout << cur << endl;
        cur -= left;
        left++;
    }
    if (cur == n && right > left)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            printf(",");
        }
        printf("[");
        for (int i = left; i <= right; i++)
        {
            if (i != right)
            {
                printf("%d,", i);
            }
            if (i == right)
            {
                printf("%d]", i);
            }
        }
    }
    
    right++;
  }
  printf("]");
  return 0;
  
}