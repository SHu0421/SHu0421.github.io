---
title: 回溯_DFS_BFS
catogory:
  - leetcode 题目汇总
tags: 回溯算法, DFS, BFS
categories:
  - leetcode
date: 2021-11-13 17:23:50
---

#### 例题
1. 字符串的转换路径问题:
    单词接龙I:只返回最短转换序列的长度（使用BFS）
    单词接龙II：返回所有最短转换序列具体是什么
    标准答案是既用到了深度优先搜索，也用到了宽度优先搜索
    （最短距离）
    首先判断endWord是否在字典中，不在的话直接返回空
    在进行单词找相邻，可以遍历单词每个字符，判断与当前是否只有一个不相等（O(mn)）；或者将当前单词的每一位替换成 26 个小写英文字母，查找是否在字典中（推荐）(O(26n));一定要注意改变了某一个位之后要记得还原该位！！！！！！
    方法1：
    - 使用BFS建立每个单词的前向节点，需要使用steps[nextWord] 记录每个单词到start的最短。
    如果steps[nextWord]==step,那么from[nextWord].insert(currentWord), 然后判断nextWord是否被vis, 或者是否还在dict中，如果在，加入队列中，进行下列操作；如果不在(已经加入过队列中或者被访问过)，直接continue
    ```C++
    // 如果从一个单词扩展出来的单词以前遍历过，距离一定更远，为了避免搜索到已经遍历到，且距离更远的单词，需要将它从 dict 中删除
    dict.erase(nextWord); //删除或者设置vis
    // 这一层扩展出的单词进入队列
    q.push(nextWord);
    // 记录 nextWord 从 currWord 而来
    from[nextWord].insert(currWord);
    // 记录 nextWord 的 step
    steps[nextWord] = step;
    ``` 
    - DFS （从endWord到startWord）反向求具体路径，同时在进入下层循环是需要判断，当前的距离是不是当前节点到start的最短距离，如果是进入循环，否则剪枝

    方法2：
    - 使用BFS求最短路，同时建立每个单词的pre单词，因为同一层两个单词可能到一个单词的距离相等，因此需要每层元素遍历完了之后再vis, 以及再队列push next_element
    next_ele.erase(unique(next_ele.begin(), next_ele.end()), next_ele.end()); //也可以直接用set来去重
    - 反向DFS求具体路径
2. 单词转换
[leetcode链接](https://leetcode-cn.com/problems/word-transformer-lcci/solution/c-python3-dfsbu-neng-hui-su-yin-wei-bu-s-u45m/)
求其中一条路径使用DFS （因为没说要最短）
求所有的路径使用BFS+DFS 在一轮访问完之后再赋值vis以及去重/或者记录每个节点d, 然后dfs的时候判断到这个节点的d时候是当前的深度对应
求最短的路径，用BFS

PS: 其他解决字符串的相关问题的方案
使用动态规划+Trie树，或者暴力string find，或者转为数组（数字）等等，

PS类似的题目： 单词接龙和最小基因变化， 最小基因变化的这道题在进行单词转换的时候，找相邻的两种方式：(1)对每个字符，4种情况 ACGT都进行测试（也就是每个字符需要验证4n次）， (2)在单词库中查找只有一个字符变化的

<font color=red>3. 组合总数 ：一定要注意如果给出的列表中包含重复的数据的话，一定要记得去重，以及通过一些条件可以提前剪枝</font>

组合总数I， II, III, VI 在进行回溯的时候需要注意的几个点：
- 每类的数据是否可以重复选择，如果可以重复选择，那么需要在递归到某一个类的时候，将这个类的所有的数据（一个或者target/candidate[i]个）都选择完
- 是只求总数还是求所有的序列，如果只求总数可以使用动态规划（一定要注意if和else的状态转移情况都要考虑到），如果求序列需要使用递归回溯剪枝
- 相同结果不用元素组合算一种还是多种（2，2，3）和（2，2，3） 原数据为（2，2，2，2，3）
- 给的列表是否包含重复的数据，如果包含需要对数据进行排序后，再进行回溯
- 给的列表是否可以重复取，如果可以那么 改为 dfs(candidates,target-k*candidates[i],i+1,count);其中count[i]=k
为了防止递归层数太深；同时一定要递归到最后pos==size&&target==0才代表找到了这样一个序列（以为count需要修改）
- 如果每个数都只能取一次，而且取的个数一定要是相等的话，可以使用二进制位进行枚举具体的序列


4. 将数组拆分为斐波拉切数列  枚举最开始的a b，求出c判断后面的字符是不是c

- 可以使用stoi将字符串转为整数（一定要注意stoi字符溢出的问题， 以及stol溢出可能性）

  long long tmp=stoi(a)+stoi(b) 如果整数相加超过了INT_MAX还是会报错，所以左边的写法是错误的，应该写为 long long tmp=stol(a)+stol(b)

- 也可以使用 回溯一个字符一个字符的累加，如果size>2的情况下计算当前数+pre是否能够达到target,如果小于那么继续循环，如果大于那么退出循环 cur = cur*10 + S[i] - '0';


5. 求图长度，或者多叉树的树高
```C++
//注意开始遍历每个节点的时候，一定要记得将根节点设置为vis
  int dfs(int cur, vector<vector<int>>& graph, vector<int> &vis){
          int ans=0;
          for(int i=0;i<graph[cur].size();i++){
              if(!vis[graph[cur][i]]){
                  vis[graph[cur][i]]=1;
                  ans= max(ans, dfs(graph[cur][i], graph, vis));
              }
          }
          return ans+1;
      }

```

6. 最小高度树（有两个类似的题目）
让根节点是排序数组的中点
使用的是拓扑排序，如果求以每个节点为根节点的树，会导致超出时间限制，因此需要使用拓扑排序，每次删除叶节点（degrees[i] ），求到最中间的几个点


7. 水壶问题，使用深度优先搜索，或者数学推导
深度优先搜索，因为超过了系统的搜索的层数，所以需要自己模拟压栈和出栈， 同时需要知道当前状态可以转化为其他状态，其他状态包括，将X倒满，将Y倒满，将X倒空，将Y倒空，将x的水导入Y中，将Y的水倒数X中 6种撞他
或者使用数学方式解决，每次水的变化量（X+Y）一定是X或者Y, 那么有不等式 ax+by=z; 那么z一定x和y最小公因数的倍数

<font color=red>8. 字典序 或者 全排列使用深度优先搜索</font>
字典序返回[1-n]所有整数
```C++
void dfs(int n, int cur, vector<int>& res){
      if(cur>n){
          return;
      }
      res.push_back(cur);//在dfs的同时push
      for(int i=0;i<=9;i++){
          dfs(n, cur*10+i, res);
      }
  }
  vector<int> lexicalOrder(int n) {
      vector<int> res;
      for(int i=1;i<=9;i++){
          dfs(n, i, res);
      }
      return res;
  }
```
```C++ 无重复数字的全排列 
方法1
void all_permute(vector<int>& nums,vector<vector<int>> &result,int cur ) {
    int size=nums.size();
    if(cur==size-1){
        result.push_back(nums);
        return;
    }
    for(int i=cur;i<size;i++){
        swap(nums[cur], nums[i]);
        all_permute(nums, result, cur+1);
        swap(nums[cur], nums[i]);
    }
}
//方法2：
void dfs(int index, string &S, string &path, vector<int> &used){
    int size=S.size();
        if(index==size){
        res.push_back(path);
        return;
    }
    for(int i=0;i<size;i++){
        if(used[i]){ //最重要的两个if判断
            continue;
        }
        path.push_back(S[i]);
        used[i]=true;
        dfs(index+1, S, path, used);
        used[i]=false;
        path.pop_back();
    }
}
```



<font color=red> 有重复数字的全排列</font>
答案解析：lc:全排列II
```C++
    sort(S.begin(), S.end()); //在主函数进行排序， 同时使用used数组，判断S中的某个字符是否被用过， 用一个string path，表示现在拼起来的字符
    void dfs(int index, string &S, string &path, vector<int> &used){
        int size=S.size();
         if(index==size){
            res.push_back(path);
            return;
        }
        for(int i=0;i<size;i++){
            if(used[i]){ //最重要的两个if判断
                continue;
            }
            if(i!=0&&S[i]==S[i-1]&&!used[i-1]){ //注意这一层的判断
                continue;
            }
            path.push_back(S[i]);
            used[i]=true;
            dfs(index+1, S, path, used);
            used[i]=false;
            path.pop_back();
        }
    }
```

扩展：排列中的下一个排列
```c++
//先找一个一个顺序相邻， 然后交换当前数和为后面第一个大于它的数，然后让后面的数递增；注意特殊情况，如果当前数已经是全排雷的最后一个，那么直接返回第一个排列
    int i=nums.size()-2;
    while(i>=0&&nums[i]>=nums[i+1]){
        i--;
    }
    if(i>=0){
        int j=nums.size()-1;
        while(nums[i]>=nums[j]){
            j--;
        }
        swap(nums[i],nums[j]);
        reverse(nums.begin()+i+1,nums.end());
    }else{
        reverse(nums.begin()+i+1,nums.end());
    }
```
lc60. 排列序列 （hard）
求全排列的第k个排列
易错点：需要最开始使用k--;因为第k个排列前面有k-1个排列
然后计算当前每一位应该放哪个第一位 前面的数为num = k/(n-1)! ，固定了第一个位, 之后更新k=k%(n-1)!
第二个位，前面的数 num = k/(n-2)! ，固定了第一个位, 之后更新k=k%(n-2)!，同时使用了一个数，需要标记为访问
重复这样的过程
```C++
string res;
k--; //非常重要
for(int j=1;j<=n;j++){
    int num=k/frac[n-j]; //前面的数
    num++; //当前应该选择的数
    // cout<<num<<endl;
    for(int i=1;i<=n;i++){
        if(!vis[i]){
            num--;
            if(num==0){
                vis[i]=1;
                res+=i+'0';
            }
        }
        
    }
    k=k%frac[n-j];
}
return res;
```

lc90, 子集II
- 题意：求有重复数据数列的所有子集
- 使用dfs+去重+路径中一直push到res中
```C++
dfs():
    res.push_back(path);
    if(index>=size){
        return;
    }
    for(int i=index;i<size;i++){
        if(i!=index&&nums[i]==nums[i-1]){ //去重方式和四数之和一样
            continue;
        }
        path.push_back(nums[i]);
        dfs(i+1, nums, path);
        path.pop_back();
    }
```

9. 01矩阵 <font color=blue>多源BFS</font>
找到1距离0的距离是从0开始进行bfs，而不是从1开始
解法：
    - 广度优先搜索+记忆数组（将为0的点放入队列中，然后一层层向外扩散，记得访问过的点记得标记为visit, 或者用matrix !=-1来判定该点时候被访问过）
    - 左上到右下；再从右下到左上

10. 大礼包。注意这道题可以学习的是状态的记忆过程，使用map<vector<int>, int>, 当然这道题直接用dfs搜索每一个状态也是可以的
注意这道题在dfs的时候，除了要循环选择每个大礼包，退出循环后，还要判断当前计算值和==全部不用大礼包==谁更小！！！
无法使用完全背包+dp解决，因为dp的内层循环无法枚举，因为是一个vector, 而不是一个简单的int


<font color=red>11. 划分为k个相同的子集：</font>
这道题既可以使用状态压缩的dp也可以使用回溯+贪心
方法一：
- 需要对数组排序，从大的数最开始进行匹配，贪心策略（这样压栈次数会更少）
- 使用回溯的时候需要使用一个vis数组，如果当前值小于target 那么继续向前遍历；如果==target那么从头开始遍历，同时k-1;如果大于target,那么循环内部判断数组下一个数是否合适  (循环数组的时候多次dfs 判断是否都能凑出<=target)
https://zhuanlan.zhihu.com/p/78031844

方法二：
- 建立n个桶，然后判断每个数应该放在哪个桶内(只用记录桶中总数，不用记录具体放到什么)；如果当前这个数放在哪个桶都不行，那么当前循环return false；仍然使用贪心减少遍历次数
- https://leetcode-cn.com/problems/partition-to-k-equal-sum-subsets/solution/liang-chong-bu-tong-de-hui-su-si-lu-cong-5rnw/


<font color =blue>12. 地图分析，多源BFS的例题</font>
和正向题目描述的思路反过来，从为1的陆地出发，而不是从每个海洋出发求最短距离。先将所有为1的节点的位置放在队列中，每访问一个节点，就修改节点位置的值，那么就不需要使用vis数组

13.组合总数||
因为这个是要求具体的组合，用dfs,同时注意去重
```C++
  for(int i=index;i<size;i++){
      if(i>index&&candidates[i]==candidates[i-1]){//去重
          continue;
      }
      path.push_back(candidates[i]);
      dfs(candidates, target-candidates[i], i+1, path);
      path.pop_back();
      // dfs(candidates, target, i+1, path); //注意这个一定不能要
  }
```


14. 面试题 16.22. 兰顿蚂蚁
    类似于走地图的题目，是一个模拟题
    因为x, y的坐标可能为负数，因此使用map< pair<int, int>, char> matrix; (使用unordered_map会报错)
    同时在进行打印的时候，应该y在外层，x在内层；如果map中没有找到这个坐标，那么应该打印出“_”, 记录当前地图的左上和右下坐标


15. 双向BFS
- 使用两个队列， 每次更新一个size比较小的队列里面的所有元素，同时使用两个unordered_map记录走到某个字符串/位置，走的步数（同时有vis数组的功能）。 如果当前更新的字符串，在另外一个队列的map中也能找到记录说明两个队列相遇了， 返回step + 1 + other[copy];

<font color=red>16. 逃脱迷宫需要移除的最少砖头数量</font>
-  使用BFS+优先队列+vis， 队列里面存放到x, y, 和到每个节点的最少要移除的砖头数量， 循环在nextx nexty=n-1的时候返回结果， 具体代码实现看模板代码/逃脱迷宫
-  不能使用dfs+记忆化数组+vis，因为到达当前节点的时候，前面vis 路径不一定是最优的，导致计算出来d不一定是最佳的，从而之后的计算都出现错误； 记忆化数组可以使用场景就是，之前的选择不会对之后的选择造成影响， 或者需要另外用一个状态位运算来记录之前走的路径到底是怎样的（见lc980, 下面有分析）
- 这道题的思路和lc752: 打开转盘锁一样，不能走回头路，lc752可以使用双端BFS，感觉这个不适合双堆队列，因为map里面的数据并不都是同一层，同时两个队列size感觉都是一样的，从两个对角线出发；这道题使用优先队列更佳
-  不一样的是这个每走一步不一定+1， 队列数据不一定在同一层（因此需要使用优先队列）， 但是逃脱迷宫是每走一步都+1， 队列里面的数据都在同一层，使用普通队列
- 总结，使用bfs查找从源到目的节点的最短路径
    1. 将源节点压入队列中，同时设置为vis
    2. 如果一层的cost一样，那么每层进行遍历（否则需要压入的时候，记录压入节点的cost）,计算当前节点的下一个节点，判断下一个节点的合理性（vis和index边缘）
    3. 如果合理，那么判断下一个节点是否是目标节点，如果是直接返回step+1,否则向队列中压入下一个节点
    4. 重复上述过程，知道队列为空
    5. 如果队列空都没有找到，说明源节点无法到达目标节点


15， 克隆图
- 使用BFS
- 这个题类似于 剑指 Offer 35. 复杂链表的复制，需要建立原始node和新node之间的映射, 同时这个hash也能充当vis数组，判断当前节点是否被访问过；复杂链表复制那道题只需要顺序两次遍历链表就可以了，不需要vis或者bfs

<font color=red>16. 给表达式添加运算符（hard）</font>
使用回溯
易错点：
    1. 乘法是有优先级的，因此之前计算dfs计算的结果有可能是需要回退一个数组，然后再进行计算
    2. 每次压入的数字可能是包含多个位的
    3. 不能包含前导0，但是这个数又不是0的情况
    ```C++
    if(i!=index&&num[index]=='0'){
        return;
    }
    ```
    4. 回溯是时候一定要记得将符号pop_back!!!!


17. lc980. 不同路径 III
- 求从起点到终点，经过二维矩阵的每个空方格（注意是每个都要走一次，而且不能重复），的不同路径总数
- 使用记忆化的dfs 因为到达每个点前面的路径是不一定相同的，因此需要使用dp[i][j][i*C+j^之前的路径] 表示到达当前的状态之前走过的路径是怎样的
注意题目表示1 <= grid.length * grid[0].length <= 20，才能使用这种位运算来记录矩阵的状态（状态压缩的条件）



18. 单词拆分II
- 需要找到所有拆分的具体方案
- 为了减少回溯的重复，使用一个hash<int, vector<string>> 将以i下标为开始后面形成的所有可能都存储下来，这样之后寻找的时候就不用重复判断 （类似二叉搜索树的所有可能那种题目）， 记忆化dfs


19. lc741. 摘樱桃(hard)
- 这道题用dp理解起来比较困难，所以使用记忆化dfs
- 易错点：贪心，第一次选最大+第二次选剩下的最大不一定是最优解
- 正确方法，需要dfs，然后需要有两条路径，就相当于同时对**两个点进行dfs**, 这两个点x1+y1=x2+y2 (有关系)然后需要判断这两个是不是同一个点，如果是，那么+grid[x1][y1]， 否则+grid[x1][y1]+grid[x2][y2]


20. lc934. Shortest Bridge 最短的桥梁
- 使用多源最短路径，两个技巧：先dfs找到岛屿上的所有点，并将将访问过的岛屿转为2；2. BFS使用层次bfs, 因为修改了访问的点为2，所以不用使用vis数组

21. lc5289. 公平分发饼干
- 题意就是如何将数组划分为k份（可以不连续）能够使得最大值最小
- 最开始以为是背包，一直找不到解法； 之后解析发现，因为数据范围比较小（数组长度最大为8），可以直接暴力应该将数组当前index的值放在哪个包里面，dfs遍历完成求最大值，和全局的最小值进行比较。



#### 总结
ok ok
1. 注意dfs和回溯还是有区别的，dfs，遇到不合适的条件可以直接退出，但是回溯，退出前要将之前的状态修改； BFS常用于求最短路径，或者最少xxxx(结合优先队列)

2. dfs和记忆化搜索和dp都有联系，有时候一道题这两种方法都可以用
例如：
- 分汤(因为都是25的倍数，所以n可以直接/25+1(如果余数不为0), 分配操作同样变为-4、-2、-1
dfs如果状态比较多，可以使用记忆化数组，同时如果状态都是某一个数的倍数，那么可以对数据进行归一化后再进行dfs
这样的话记忆化搜索的状态数量就会减少
```C++
 double ans = 0.0;
                if (i == 0) ans = 1.0;
                if (i == 0 && j == 0) ans = 0.5;
                if (i > 0 && j > 0) {
                    ans = 0.25 * (memo[M(i-4)][j] + memo[M(i-3)][M(j-1)] +
                                  memo[M(i-2)][M(j-2)] + memo[M(i-1)][M(j-3)]);
                }
```
- 类似的概率转移dfs/dp有leet935. 马”在棋盘上的概率（可以最后/pow(8,N), 不用每次/8）

3. 如果要求岛屿的形状相同，那么可以将岛屿的位置使用string的形式存储下来，然后使用set<string>来存储，返回size就是形状不同的岛屿（忽略翻折和旋转）

4. 递归转为非递归的方式，使用堆或者栈（lc100.相同的数（dfs/宽度优先遍历））

5. 注意如果dfs中数据包含重复，一定要记得去重（如排列，组合）

6. 如果数据范围比较小的情况，可以直接dfs 暴力每种情况求答案 （lc5289.公平分发饼干）

