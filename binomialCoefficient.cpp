#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll memo[52][52];
ll ck(int i, int j){
  if(j > i) return 0;
  if(i == j || j == 0) return 1;
  ll& ans = memo[i][j];
  if(ans != -1) return ans;
  return ans = ck(i-1, j-1) + ck(i-1, j);
}

int main(){
  memset(memo, -1, sizeof(memo));
  cout << ck(3,2) << '\n';
}