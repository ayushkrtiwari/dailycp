// https://www.geeksforgeeks.org/problems/diameter-of-binary-tree/1

/*
class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = NULL;
        right = NULL;
    }
};

Node* newNode(int val) {
    return new Node(val);
}
*/

class Solution 
{
    public:
        int mxdis = 0;
    // int lca(Node* tmp, int u, int v)
    // {
    //     if(tmp == NULL) return 0;
    //     if(tmp -> data == u) return u;
    //     if(tmp -> data == v) return v;
    //     if((lca(tmp -> left, u, v) == u and lca(tmp -> right, u, v) == v) or (lca(tmp -> left, u, v) == v and lca(tmp -> right, u, v) == u))
    //     return tmp -> data;
    //     if(lca(tmp -> left, u, v) == v or lca(tmp -> right, u, v) == v) return v;
    //     if(lca(tmp -> left, u, v) == u or lca(tmp -> right, u, v) == u) return u;
    //     return lca(tmp -> left, u, v) or lca(tmp -> right, u, v);
    // }
    // void dfs(Node* temp, map<int,int> &dep, int lastvisited)
    // {
    //     if(temp == NULL) return;
    //     dep[temp -> data] = dep[lastvisited] + 1;
    //     lastvisited = temp -> data;
    //     dfs(temp -> left, dep, lastvisited);
    //     dfs(temp -> right, dep, lastvisited);
    // }
    int dfsdmtr(Node* tmp)
    {
        // if((tmp -> left -> data) == NULL and (tmp -> right -> data) == NULL) return 0;
        if(tmp == NULL) return -1;
        int left = 1 + dfsdmtr(tmp -> left);
        int right = 1 + dfsdmtr(tmp -> right);
        mxdis = max(mxdis, left + right);
        return max(left, right);
    }
    // void dfsnode(Node* tmp)
    // {
    //     if(tmp == NULL) return;
    //     dfsdmtr(tmp);
    //     dfsnode(tmp -> left);
    //     dfsnode(tmp -> right);
    // }
    int diameter(Node* root) {
        // Your code here
        // vector<int> dep(n + 1, 0);
        Node* tmp = root;
        dfsdmtr(tmp);
        return mxdis;
    }
};