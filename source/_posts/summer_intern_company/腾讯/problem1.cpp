// 本题为考试单行多行输入输出规范示例，无需提交，不计分。
#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n,m;
    scanf("%d%d", &n, &m);
    vector<float> arr(m);
    for(int i=0;i<m;i++){
        scanf("%f", &arr[i]);
    }
    cout<<n<<" "<<m<<endl;
    int cur=n;
    for(int i=0;i<m;i++){
        float after=cur/(1-arr[i])-1;
        cur=after;
    }
    cout<<cur<<endl;
    return 0;
}