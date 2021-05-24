//Matrix exponenciation in O(logN) time complexity
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
typedef long long ll;
typedef vector<vector<ll>> mat;
mat identity(const int n){
  mat m(n, vector<ll>(n));
  for(int i = 0; i < n ; ++i){
    for(int j = 0; j < n ; ++j){
      m[i][j] = (i == j);
    }
  }
  return m;
}
mat mul(mat& a, mat& b){
  mat c((int)a.size(), vector<ll>((int)b[0].size(), 0LL));
  for(int i = 0; i < (int)a.size() ;  ++i){
    for(int j = 0; j < (int)b[0].size() ; ++j){
      for(int k = 0; k < (int)b.size() ; ++k){
        c[i][j] += (a[i][k]%mod)*(b[k][j]%mod)%mod;
        c[i][j]%=mod;
      }
    }
  }
  return c;
}

mat powMat(mat a, ll n){
  if(n == 0) return identity((int)a.size());
  mat b = powMat(a, n/2);
  b = mul(b,b);
  if(n%2) b = mul(b,a);
  return b;
}