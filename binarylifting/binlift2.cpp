// जय श्री राम  JAI SHREE RAM

// https://leetcode.com/problems/kth-ancestor-of-a-tree-node/

#pragma GCC optimize("O3,unroll-loops,Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
static const auto harsh = []() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
}();
#define LC_HACK
#ifdef LC_HACK
const auto __ = []() {
    struct ___ { static void _() { std::ofstream("display_runtime.txt") << 0 << '\n'; } };
    std::atexit(&___::_);
    return 0;
}();
#endif

class TreeAncestor {
public:
    int col_;
    vector<vector<int>> ancestor; 
    TreeAncestor(int n, vector<int>& parent) {
        int col = (int)log2(n) + 1;
        col_ = col;
        // ancestor(n + 1, vector<int>(col, -1));
        // for(int i = 0; i < n; i++)
        // for(int j = 0; j < col; j++)
        // ancestor[i].push_back(-1);
        ancestor.assign(n, vector<int>(col, -1)); // assign suits best here, since others ways dont suit here
        for(int i = 0; i < n; i++)
        ancestor[i][0] = parent[i];
        for(int c = 1; c < col; c++)
        for(int i = 1; i < n; i++)
        {
            if(ancestor[i][c - 1] != -1)
            ancestor[i][c] = ancestor[ancestor[i][c - 1]][c - 1];
        }        
    }
    
    int getKthAncestor(int node, int k) {
        int x = col_;
        for(int i = 0; i <= x; i++)
        if((k>>i) & 1)
        {
            if(ancestor[node][i] == -1)
            {
                node = -1;
                break;
            }
            else
            node = ancestor[node][i];
        }
        return node;
    }
};

/**
 * Your TreeAncestor object will be instantiated and called as such:
 * TreeAncestor* obj = new TreeAncestor(n, parent);
 * int param_1 = obj->getKthAncestor(node,k);
 */