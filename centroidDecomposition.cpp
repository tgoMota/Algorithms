//Centroid Decomposition
//Runs in O(NlogN) time complexity
#include <bits/stdc++.h>
using namespace std;

struct CentroidDecomposition{
  int N;
  vector<vector<int>> tree, decTree;
  vector<int> size, parent;
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
    for(int x : tree[v]){
      if(x!=p && !isCentroid[x] && 2*size[x] >= n) return getCentroid(x, v, n);
    }
    return v;
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
        decTree[cent_root].push_back(cent_sub);
        decTree[cent_sub].push_back(cent_root);
        parent[cent_sub] = cent_root;
      }
    }
    return cent_root;
  }
};

int main(){
  int n;
  cin >> n;
  CentroidDecomposition cd(n);
  for(int i = 0; i < n-1 ; ++i){
    int u, v;
    cin >> u >> v;
    cd.add_edge(u,v);
  }
  int root = cd.decomposeTree(0);
  cout << root << '\n';
  return 0;
}
