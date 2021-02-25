//LCA with Binary Lifting
//Fast way to answer querys of Lowest Common Ancestor(LCA) betweem two nodes in a tree
//O(V*log2(V)+E) to calculate all the states of the DP
//O(log2(V)) to solve the LCA
#include <bits/stdc++.h>
using namespace std;
struct liftLCA{
    int log, N, root;
    vector<vector<int>> adj, memo;
    vector<int> lv;
    liftLCA(){}
    liftLCA(int _root, const int n){
    	root = _root;
        N = n;
        log = (int)log2(n)+1;
        lv.assign(n+1, 0);
        memo.assign(n+1, vector<int>(log+1, -1));
        dfs(root,root);
    }

    void dfs(int v, int p){
        lv[v] = lv[p]+1;
        memo[v][0] = p;
        for(int i = 1; i <= log ; ++i){
            memo[v][i] = memo[memo[v][i-1]][i-1];
        }
        for(int x : adj[v]){
            if(x != p) continue;
            dfs(x, v);
        }
    }

    int lca(int u, int v){
        if(lv[u] < lv[v]) swap(u,v);
        int diff = lv[u]-lv[v];
        for(int i = 0; i <= log ; ++i){
            if((1<<i) & diff) u = memo[u][i];
        }
        if(u == v) return u;
        for(int i = log ; i >= 0 ; --i){
            if(memo[u][i] != memo[v][i]){
                u = memo[u][i];
                v = memo[v][i];
            }
        }
        return memo[u][0];
    }
};

int main(){
    return 0;
}
