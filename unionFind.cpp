#include <bits/stdc++.h>
using namespace std;
//Union find by size
struct UF{
  vector<int> p, sz;
  UF(){};
  UF(const int n){
    init(n);
  }
  void init(const int n){
    p.assign(n+1, -1);
    sz.assign(n+1, 1);
    for(int i = 0; i <= n ; ++i) p[i] = i;
  }
  
  int find_set(int u){
    return p[u] = (p[u] == u ? u : find_set(p[u]));
  }
  
  void union_set(int a, int b) {
      a = find_set(a);
      b = find_set(b);
      if (a != b) {
          if (sz[a] < sz[b]) swap(a, b);
          p[b] = a;
          sz[a] += sz[b];
      }
  }
};

int main(){
  
}