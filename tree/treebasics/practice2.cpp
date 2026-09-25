// https://www.geeksforgeeks.org/problems/ancestors-in-binary-tree/1

/*
Structure of a node is as following
struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
};
*/

class Solution {
    public:
    // bool isAncestor(int u , int v)
    // {
    //     return tin[u] <= tin[v] && tout[u] >= tout[v]
    // }
    // int timer = 0;
    // vector<int> tin(n + 1);
    vector<int> printanc;
    int ancestor(struct Node* temp, int u)
    {
        if(temp == NULL) return 0;
        if(temp == NULL) return 0;
        if(temp -> data == u) return u;
        if(ancestor(temp -> left, u) == u)
        {
            printanc.push_back(temp -> data);
            return u;
        }
        if(ancestor(temp -> right, u) == u)
        {
            printanc.push_back(temp -> data);
            return u;
        }
        return 0;
    }
    // Function should return all the ancestor of the target node
    vector<int> Ancestors(struct Node *root, int target) {
        // Code here
        struct Node* tmp = root;
        ancestor(tmp, target);
        return printanc;
    }
};

// LCA or Ancestor is done by 3 ways:
// recursion return in array tree       |
// recursion return in struct tree      | Refer striver video
// prefix order in out timer traversal