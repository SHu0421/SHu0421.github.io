//一些注意的地方： 1. 一定要将pre最开始的赋值为NULL 2. table最开始的每个元素也是赋值为NULL
// 通用模板 https://github.com/aozturk/HashMap/tree/master/hashmap
#include<iostream>
#include<vector>

using namespace std;

struct hashNode{
    int key;
    int val;
    hashNode *next;
};

class MyHashMap
{
    private:
    vector<hashNode*> table;
    int size;
    public:
    MyHashMap(int _size){
        size = _size;
        // 最开始的时候并不需要初始化，只需要全部为null即可
        for (int i = 0; i < size;i++){
            table.push_back(NULL);
        } 
    }
    //析构的时候需要删除每一个指针
    ~MyHashMap(){
        for (int i = 0; i < size;i++){
            hashNode *cur, *pre;
            cur = table[i];
            while(cur!=nullptr){
                pre = cur;
                cur = cur->next;
                delete pre;
            }
        }
    }
    
    // 取模作为hash函数
    int hashFunc(int key){
        return key & (size - 1);
    }
    void put(int key, int val){
        int index = hashFunc(key);
        // cout << index << endl;
        hashNode *cur, *pre=NULL;
        cur = table[index];
        bool flag = false;
        while (cur != nullptr)
        {
            if(cur->key==key){
                flag = true;
                cur->val = val;
                break;
            }else{
                pre = cur;
                cur = cur->next;
            }
        }
        if(!flag){
            if(pre==NULL){
                table[index] = new hashNode();
                table[index]->key = key;
                table[index]->val = val;
                // cout << "finish put val" << endl;
            }
            else
            {
                hashNode *tmp = new hashNode();
                tmp->key = key;
                tmp->val = val;
                pre->next = tmp;
            }
        }
    }

    void remove(int key){
        int index = hashFunc(key);
        hashNode *cur, *pre=NULL;
        cur = table[index];
        bool flag = false;
        while (cur != nullptr)
        {
            if(cur->key==key){
                flag = true;
                if(pre==NULL){
                    table[index] = cur->next; //注意这个，但是如果后面是null 也没问题
                }else{
                     pre->next = cur->next;
                }
                delete cur;
                break;
            }
            pre = cur;
            cur = cur->next;
        }
    }

    bool get(int key, int& value){
        int index = hashFunc(key);
        hashNode *cur;
        cur = table[index];
        bool flag = false;
        while (cur != nullptr)
        {
            if(cur->key==key){
                value = cur->val;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }
};

int main(){
    MyHashMap *myHashMap= new MyHashMap(8);
    int val;
    cout << myHashMap->get(1, val) << endl;
    myHashMap->put(1, 3);
    cout << myHashMap->get(1, val) << endl;
    cout << val << endl;
    myHashMap->put(1, 2);
    cout << myHashMap->get(1, val) << endl;
    cout << val << endl;
    myHashMap->put(2, 5);
    myHashMap->put(5, 5);
    myHashMap->put(7, 5);
    cout << myHashMap->get(7, val) << endl;
    cout << myHashMap->get(6, val) << endl;
    return 0;
}