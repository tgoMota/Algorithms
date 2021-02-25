//Centroid Decomposition
//Runs in O(NlogN) time complexity
#include <bits/stdc++.h>
using namespace std;
#define oo 0x3f3f3f3f
#define fastio() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)

struct CentroidDecomposition{
  int N, log;
  vector<vector<int>> tree, decTree;
  vector<int> size, lv;
  vector<bool> isCentroid;
  CentroidDecomposition(){}
  CentroidDecomposition(const int n){
    N = n+1;
    tree.assign(N, vector<int>());
    decTree.assign(N, vector<int>());
    size.assign(N, 0);
    isCentroid.assign(N, false);
  }

  void add_edge(int u, int v){
    tree[u].push_back(v);
    tree[v].push_back(u);
  }

  void dfs(int v, int p){
    size[v] = 1;
    for(int x : tree[v]){
      if(x != p && !isCentroid[x]){
        dfs(x, v);
        size[v] += size[x];
      }
    }
  }

  int getCentroid(int v, int p, int n){
    bool is_centroid = true;
    int heaviest_child = 0;
    for(int x : tree[v]){
      if(x != p && !isCentroid[x]){
        if(size[x] > n/2) is_centroid = false;
        if(heaviest_child == 0 || size[x] > size[heaviest_child]) heaviest_child = x;
      }
    }
    if(is_centroid && n-size[v] <= n/2) return v;
    return getCentroid(heaviest_child, v, n);
  }

  int getCentroid(int v){
    dfs(v, -1);
    int centroid = getCentroid(v, -1, size[v]);
    isCentroid[centroid] = true;
    return centroid;
  }

  int decomposeTree(int v){
    int cent_root = getCentroid(v);
    for(int x : tree[cent_root]){
      if(!isCentroid[x]){
        int cent_sub = decomposeTree(x);
        parent[cent_sub] = cent_root;
        decTree[cent_root].push_back(cent_sub);
        decTree[cent_sub].push_back(cent_root);
      }
    }
    return cent_root;
  }
}; 