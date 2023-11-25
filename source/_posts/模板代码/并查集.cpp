int N = 1000;
// (1)朴素并查集：
int p[N]; //存储每个点的祖宗节点
// 返回x的祖宗节点
int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void uni(int a, int b){
    // 合并a和b所在的两个集合：
    p[find(a)] = find(b);
}

int main(){
    // 初始化，假定节点编号是1~n
    for (int i = 1; i <= N; i ++ ) p[i] = i;
}





// (2) 带size的并查集， 维护每个并查集包含元素个数
int p[N], size[N];
//p[]存储每个点的祖宗节点, size[]只有祖宗节点的有意义，表示祖宗节点所在集合中的点的数量

// 返回x的祖宗节点
int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void uni(int a, int b){
    // 合并a和b所在的两个集合：
    p[find(a)] = find(b);
    size[b] += size[a];
}

int main(){
        // 初始化，假定节点编号是1~n
    for (int i = 1; i <= N; i ++ )
    {
        p[i] = i;
        size[i] = 1;
    }
}



//(3) 维护并查集的数量
int p[N];
int count = 0;


// 返回x的祖宗节点
int find(int x)
{
    if(p[x]==-1){
        p[x] = x;
        count++ ;
        return x;
    }
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}

void uni(int a, int b){
    // 合并a和b所在的两个集合：
    int fa = find(a);
    int fb = find(b);
    if(fa!=fb){
        p[fa] = fb;
        count-- ;
    }
    
}

int main(){
        // 初始化，假定节点编号是1~n
    for (int i = 1; i <= N; i ++ )
    {
        p[i] = -1;
    }
}


//(4) 维护距离的并查集
int p[N], d[N];
//p[]存储每个点的祖宗节点, d[x]存储x到p[x]的距离

// 返回x的祖宗节点
int find(int x)
{
    if (p[x] != x)
    {
        int u = find(p[x]);
        d[x] += d[p[x]];
        p[x] = u;
    }
    return p[x];
}

void uni(int x, int y){
    // 合并a和b所在的两个集合：
    p[find(a)] = find(b);
    d[find(a)] = distance; // 根据具体问题，初始化find(a)的偏移量
}


int main(){
    // 初始化，假定节点编号是1~n
    for (int i = 1; i <= N; i ++ )
    {
        p[i] = i;
        d[i] = 0;
    }
}






/*
//其他奇异技巧
1. 不一定都是使用数组， 可以直接使用hash_map表示父子关系
    a. string作为头节点， unordered_map<string, string>father 
    b. int 作为头结点：unordered_map<int, int> father
    c. 在查找要判断 if (father.find(x) == father.end()) father[x] = x; count++;
*/

//参考链接：
// https://www.acwing.com/blog/content/398/






