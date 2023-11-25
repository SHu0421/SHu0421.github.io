//二叉树

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Codec {
public:
    
    // Encodes a tree to a single string.
    string traverse(TreeNode* root){
        if(root==NULL){
            return "#";
        }
        return to_string(root->val)+" "+traverse(root->left)+" "+traverse(root->right);
    }
    string serialize(TreeNode* root) {
        string res = traverse(root);
        cout<<res<<endl;
        return res; 
    }

    TreeNode* buildTree(string data, int &i){
        int size=data.size();
        while(i<size&&data[i]==' '){
            i++;
        }

        if(i==size||data[i]=='#'){
            i++;
            return NULL;
        }
        bool neg=false;
        if(data[i]=='-'){
            neg=true;
            i++;
        }
        int tmp=0;
        
        while(i<size&&isdigit(data[i])){
            tmp=tmp*10+data[i]-'0';
            i++;
        }
        if(neg){
            tmp=-tmp;
        }

        TreeNode *root=new TreeNode(tmp);
        root->left=buildTree(data, i);
        root->right=buildTree(data, i);
        return root;
    }
    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        int pos=0;
        TreeNode *root=buildTree(data, pos);

        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));



//N叉树的序列化和反序列化
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/

class Codec {
public:
    string res;
    string dfs(Node* root){

        if(root==NULL){
            return ""; //有> return 所以不需要再加 #了
        }
        string data;
        int size=root->children.size();
        data+=to_string(root->val);
        for(int i=0;i<size;i++){
            data+=dfs(root->children[i]);
        }
        return "<"+data+">";
    }
    // Encodes a tree to a single string.
    string serialize(Node* root) {
       string res = dfs(root);
       cout<<res<<endl;
       return res;
    }
	
    Node* buildTree(string data){
        int size=data.size();
        stack<Node*> node_stack;
        Node* head=new Node();
        Node* cur=head;
       
        for(int i=0;i<size;i++){
            if(data[i]=='<'){
                node_stack.push(cur);
            }else if(data[i]=='>'){
                cur=node_stack.top();
                node_stack.pop();
                
            }else if(isdigit(data[i])){
                int tmp=0;
                while(i<size&&isdigit(data[i])){
                    tmp=tmp*10+data[i]-'0';
                    i++;
                }
                 Node* new_node=new Node();
                 new_node->val=tmp;
                node_stack.top()->children.push_back(new_node);
                cur=new_node;
                i--;
            }
        }
        return head;
    }
    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
         if(data==""){
            return NULL;
        }
        Node* root=buildTree(data);
        int pos=0;
        return root->children[0];
    }
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));