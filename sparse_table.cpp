#include <bits/stdc++.h>
using namespace std;
struct sparse_table{
  const int MAX_LOG = 25;
  vector<vector<int>> t;
  vector<int> lg;
  int n;
  sparse_table(){};
  sparse_table(vector<int>& v){
    n = (int)v.size();
    lg.assign(n+1, 0);
    t.assign(n+1, vector<int>(MAX_LOG+1,0));
    for(int i = 2; i <= n; ++i) lg[i] += lg[i/2]+1;
    for(int i = 0; i < n ; ++i) t[i][0] = v[i];
    for(int j = 1; j <= MAX_LOG ; ++j){
      for(int i = 0; i + (1 << j) <= n; ++i){
        t[i][j] = __gcd(t[i][j-1],t[i+(1<<(j-1))][j-1]) ;
      }
    }
  }

  int query(int l, int r){
    int j = lg[r-l+1];
    return __gcd(t[l][j],t[r-(1<<j)+1][j]);
  }
};