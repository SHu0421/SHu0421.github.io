/*  题意：将一个二进制数转为0，需要的最少操作次数
只允许两种操作：1.i th数位可以转换，当前仅当i+1 位上为1，同时i+1后面的数都为0
              2. 最右边的数可以随意转换*/

//解决方案递归：
// https://leetcode.cn/problems/minimum-one-bit-operations-to-make-integers-zero/solution/hua-shan-yi-tiao-dao-wo-men-di-gui-zhao-zou-by-luc/

#include<iostream>
#include<vector>

using namespace std;


// 下面这个使用互相调用，所以有问题
// int changeHigestBitToOne(int n, int bit, vector<int> &dp){
//     if(n&(1<<bit)){
//         return minNum(n|(1<<bit));
//     }else{
//         return changeHigestBitToOne(n, bit-1, dp)+1+dp[bit-1];
//     }
// }
// int minNum(int n){
//     int index=0;
//     int tmp=n;
//     int higest_index=0;
//     while(tmp){
//         tmp=tmp>>1;
//         higest_index++;
//     }
//     higest_index--;
//     if(n==1){
//         return 1;
//     }
//     if(n==0){
//         return 0;
//     }
//     int res=0;
//     vector<int> dp(index, 0);
//     dp[0]=1;
//     for(int i=1;i<index;i++){
//         dp[i]=dp[i-1]*2+1;
//     }
//     if(n&(1<<(higest_index-1))){ //次高位为1
//         int tmp_num=n;
//         tmp_num|=(1<<higest_index);
//         tmp_num|=(1<<(higest_index-1));
//         res=minNum(tmp_num);//递归子问题
//     }else{//次高位不为1
//         int tmp_num=n;
//         tmp_num|=(1<<higest_index);
//         res=changeHigestBitToOne(tmp_num, higest_index-1, dp);
//     }
//      res += dp[higest_index-1];

//      return res;
// }


// 只需要考虑将第一个1置为0，然后加上 后面一位 010000的所有值置为0 就可以得到最终结果
// 10000 规律得到置为0需要的操作数 dp
//1000100xxx 子问题转为1000100000 +循环 转为1100000的情况
//11000xxx 子问题 转为110000 000

int compute(vector<int> &bit_nums, int index, vector<int> &dp){
    int size=bit_nums.size();
    // 跳过头0,找到第一个1
    while(index<size&&bit_nums[index]==0){
        index++;
    }
    
    if(index>=size){
        return 0;
    }
    if(index==size-1){
        return 1; 
    }
    int res=0;
    if(bit_nums[index+1]){//如果第一个后面一位也为1, 11xxxxx模式
        res = compute(bit_nums, index+2, dp) + 1 + dp[size-index-2];
        cout<<compute(bit_nums, index+2, dp)<<endl;
        // cout<<size-index-1<<" "<< dp[size-index-1]<<endl;
    }else{
        //找到后面第一个1， change他后面为0 + 1， 形成一个中间为0个个数的循环
        int tmp=index+1;
        while(tmp<size&&bit_nums[tmp]==0){
            tmp++;
        }
        if(tmp==size){//后面没有1了，直接返回结果
            res = dp[size-index-2];
        }else{ // 100001xxx这种模式, 使用循环，将1前面置为1， 后面置为0；知道转化为将第一个1置为0， 然后后面的就是dp[size-(index+1)-1]
            res+=compute(bit_nums, tmp+1, dp);//tmp 最后面置为0
            for(int j=tmp;j>=index+1;j--){
                res+= 1 + dp[size-j-1];
                cout<<1+dp[size-j-1]<<endl;
            }
        }
    }
    return res;
}
int solve(int n){
    vector<int> bit_nums;
    if(n==0){
        return 0;
    }
    if(n==1){
        return 1;
    }
    while(n){
        bit_nums.push_back(n&1);
        n=n>>1;
    }
    reverse(bit_nums.begin(), bit_nums.end());
    
    int bit_num=bit_nums.size();
    for(int i=0;i<bit_num;i++){
        cout<<bit_nums[i];
    }
    cout<<endl;

    vector<int> dp(bit_num, 0);
    dp[0]=1;
    //只有1位二进制全部置为0需要的操作数目
    for(int i=1;i<bit_num;i++){
        dp[i]=dp[i-1]*2+1;
    }

    int res = compute(bit_nums, 0, dp);
    return res;
}

int main(){
    cout<<"hello world"<<endl;
    // cout<<solve(4)<<endl; //7
    // cout<<solve(13)<<endl; //9
    cout<<solve(11)<<endl; //13
    return 0;
}