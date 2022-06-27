vector<int> match;
vector<bool> vst;
vector<vector<int>> adj;
int Aug(int l) {
  if (vst[l]) return 0;
  vst[l] = 1;
  for (int x : adj[l]) {
    if (match[x] == -1 || Aug(match[x])) {
      match[x] = l; 
      return 1;
    } 
  }
  return 0;
}
 
int kuhn(const int n, const int m){ //n => size of left side //m => size of right side
  int ans = 0;
  match.assign(m+1, -1);
  for (int l = 0; l < n ;l++) { //0-indexed //if 1-indexed change to (l = 1; l <= n ; l++)
    vst.assign(n+1, 0);
    ans += Aug(l);
  }
  return ans;
}
