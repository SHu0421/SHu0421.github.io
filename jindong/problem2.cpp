#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct edge{
    int start;
    int end;
    int weight;
};

bool cmp(edge &a, edge &b){
    return a.weight > b.weight;
}
vector<int> father;
int findFather(int x)
{
    if(father[x]!=x){
        father[x] = findFather(father[x]);
    }
    return father[x];
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<edge> edges;

    while (m)
    {
        int s, e, p;
        scanf("%d%d%d", &s, &e, &p);
        edge tmp;
        tmp.start = s;
        tmp.end = e;
        tmp.weight = p;
        edges.push_back(tmp);
        m--;
    }
    sort(edges.begin(), edges.end(), cmp);
    father=vector<int>(n+1, 0);
    for (int i = 1; i <=n;i++){
        father[i] = i;
    }
    int res = INT_MAX;
    for (int i = 0; i < edges.size(); i++)
    {
        int a = edges[i].start;
        int b = edges[i].end;
        int fa = findFather(a);
        int fb = findFather(b);
        if (fa!=fb){
            res = min(edges[i].weight, res);
            father[fa] = fb;
        }
    }
    cout << res << endl;
    return 0;
}