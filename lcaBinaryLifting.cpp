//LCA with Binary Lifting
//Fast way to answer querys of Lowest Common Ancestor(LCA) betweem two nodes in a tree
//O(V*log2(V)+E) to calculate all the states of the DP
//O(log2(V)) to solve the LCA
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj, memo;
vector<int> lv;
void dfs(int v, int p, const int logn){
    lv[v] = lv[p]+1;
    memo[v][0] = p;
    for(int i = 1; i <= logn ; ++i){
        memo[v][i] = memo[memo[v][i-1]][i-1];
    }
    for(int x : adj[v]){
        if(memo[x][0] != -1) continue;
        dfs(x, v, logn);
    }
}

void build(const int n){
    int logn = (int)log2(n)+1;
    lv.assign(n, 0);
    memo.assign(n+1, vector<int>(logn+1, -1));
    dfs(0,0,logn);
}

int lca(int u, int v, const int n){
    if(lv[u] < lv[v]) swap(u,v);
    int diff = lv[u]-lv[v];
    int logn = (int)log2(n)+1;
    for(int i = 0; i <= logn ; ++i){
        if((1<<i) & diff) u = memo[u][i];
    }
    if(u == v) return u;
    for(int i = logn ; i >= 0 ; --i){
        if(memo[u][i] != memo[v][i]){
            u = memo[u][i];
            v = memo[v][i];
        }
    }
    return memo[u][0];
}
