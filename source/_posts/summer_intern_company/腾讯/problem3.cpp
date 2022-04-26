// 本题为考试单行多行输入输出规范示例，无需提交，不计分。
#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> red(n);
    vector<int> blue(m);
    for(int i=0;i<n;i++){
         scanf("%d", &red[i]);
    }
    
    for(int i=0;i<m;i++){
        scanf("%d", &blue[i]);
    }
    sort(red.begin(), red.end());
    sort(blue.begin(), blue.end());
    int q=0;
    scanf("%d", &q);
    vector<int> ans(3);
    for(int i=0;i<q;i++){
        int l, r;
        
        scanf("%d%d", &l, &r);
        int l_index=lower_bound(red.begin(), red.end(), l)-red.begin();
        int r_index=upper_bound(red.begin(), red.end(), r)-red.begin();
        int r_size=r_index-l_index;

        l_index=lower_bound(blue.begin(), blue.end(), l)-blue.begin();
        r_index=upper_bound(blue.begin(), blue.end(), r)-blue.begin();
        int b_size=r_index-l_index;
        if(b_size<r_size){
            ans[0]++;
        }else if(b_size==r_size){
            ans[1]++;
        }else{
            ans[2]++;
        }
    }
    for(int i=0;i<3;i++){
        cout<<ans[i]<<endl;
    }
    return 0;
}