//compute (a^b)%m
//O(log b)
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll mod_pow(ll a, ll b, ll m){
 a%=m;
 ll ans = 1LL;
 while(b){
  if(b&1) ans = ans * a % m;
  a = a*a % m;
  b >>= 1;
 }
 return ans;
}