#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// popcount shortcut
inline int pc(int x) { return __builtin_popcount(x); }

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, C;
    cin >> R >> C;
    vector<string> A(R);
    for(int i = 0; i < R; i++){
        cin >> A[i];
    }

    // 8 neighbors
    int dr[8] = {-1,-1,-1, 0,0, 1,1,1};
    int dc[8] = {-1, 0, 1,-1,1,-1,0,1};

    // 1) compute "safe" bitmask for each row
    vector<int> safe(R,0);
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            if(A[i][j]!='-') continue;
            bool ok = true;
            for(int d=0;d<8;d++){
                int ni=i+dr[d], nj=j+dc[d];
                if(ni>=0&&ni<R&&nj>=0&&nj<C&&A[ni][nj]=='@'){
                    ok=false;
                    break;
                }
            }
            if(ok) safe[i] |= 1<<j;
        }
    }

    // 2) build all legal masks per row
    vector<vector<int>> masks(R);
    for(int i=0;i<R;i++){
        int full = safe[i];
        // iterate subsets of full
        for(int m = full; ; m = (m-1)&full){
            // no two horizontal neighbors
            if((m & (m<<1))==0) 
                masks[i].push_back(m);
            if(m==0) break;
        }
    }

    // 3) DP array: dp[r][i][j] = best if row r uses masks[r][i] and r-1 uses masks[r-1][j].
    // We only need to keep two slices in memory.
    vector<vector<ll>> dp_prev, dp_cur;
    
    // -- Base for row 0  (no r-1)
    dp_prev.assign(masks[0].size(), vector<ll>(1,0));
    for(int i=0;i<(int)masks[0].size();i++){
        dp_prev[i][0] = pc(masks[0][i]);
    }
    if(R==1){
        ll ans=0;
        for(auto &v:dp_prev) ans = max(ans,v[0]);
        cout<<ans<<"\n";
        return 0;
    }

    // -- Row 1, uses dp_prev (row0)
    dp_cur.assign(masks[1].size(), vector<ll>(masks[0].size(), 0));
    for(int i=0;i<(int)masks[1].size();i++){
        int m1 = masks[1][i];
        int c1 = pc(m1);
        for(int j=0;j<(int)masks[0].size();j++){
            int m0 = masks[0][j];
            int forbid = m0 | (m0<<1) | (m0>>1);
            if((m1 & forbid)==0){
                dp_cur[i][j] = dp_prev[j][0] + c1;
            }
        }
    }
    dp_prev.swap(dp_cur);               // now dp_prev[r=1][i][j] and second dim size=masks[0]

    if(R==2){
        ll ans=0;
        for(auto &row:dp_prev)
            for(ll v:row) ans=max(ans,v);
        cout<<ans<<"\n";
        return 0;
    }

    // -- Rows 2..R-1
    // We’ll roll dp through r=2..R-1. At each step:
    //  dp_prev  stores dp[r-1][ * ][ * ] with dims [|masks[r-1]|][|masks[r-2]|]
    //  dp_cur   will store dp[r][   * ][ * ] with dims [|masks[r]|][|masks[r-1]|]

    for(int r=2;r<R;r++){
        int M   = masks[r].size();
        int M1  = masks[r-1].size();
        int M2  = masks[r-2].size();
        dp_cur.assign(M, vector<ll>(M1, 0));

        for(int i=0;i<M;i++){
            int m   = masks[r][i];
            int cnt = pc(m);
            // precompute nothing here: just loop j,k
            for(int j=0;j<M1;j++){
                // check row r vs r-1 adjacency
                int pm1 = masks[r-1][j];
                int forbid1 = pm1 | (pm1<<1) | (pm1>>1);
                if(m & forbid1) continue;

                for(int k=0;k<M2;k++){
                    ll prevVal = dp_prev[j][k];
                    if(prevVal<0) continue;  // unreachable state
                    int pm2 = masks[r-2][k];
                    // compute the "influence" of pm2 on row r-1:
                    int infl = pm2 | (pm2<<1) | (pm2>>1);
                    // those bits sit in row r-1; they block diagonals into row r
                    if( (m & (infl<<1)) || (m & (infl>>1)) )
                        continue;

                    // valid transition
                    dp_cur[i][j] = max(dp_cur[i][j], prevVal + cnt);
                }
            }
        }

        // roll forward
        dp_prev.swap(dp_cur);
    }

    // final answer in dp_prev (for r=R-1):
    ll ans = 0;
    for(auto &row: dp_prev)
        for(ll v: row)
            ans = max(ans, v);

    cout << ans << "\n";
    return 0;
}
