//Maximum flow - Dinic's algorithm
//Runs in O(EV^2)
//ref: https://cp-algorithms.com/graph/dinic.html
#include <bits/stdc++.h>
using namespace std;
#define ooLL 0x3f3f3f3f3f3f3f3f
typedef long long ll;
struct Dinic{
  struct edge{
    int u, v;
    ll cap, flow = 0LL;
    edge(){}
    edge(int _u, int _v, ll _cap){
      u = _u;
      v = _v;
      cap = _cap;
      flow = 0LL;
    }
  };
  vector<vector<int>> adj;
  vector<edge> edges;
  vector<int> lv, ptr;
  int S, T, N, cnt = 0;
  Dinic(){}
  Dinic(const int s, const int t, const int _N){
    S = s;
    T = t;
    N = _N;
    adj.assign(N+5, vector<int>());
  }

  void add_edge(int u, int v, ll cap){
    adj[u].push_back(cnt++);
    adj[v].push_back(cnt++);
    edges.push_back(edge(u,v,cap));
    edges.push_back(edge(v,u,0));
  }

  bool bfs(){
    queue<int> q;
    q.push(S);
    lv.assign(N+5, -1);
    lv[S] = 0;
    while(!q.empty()){
      int u = q.front();
      q.pop();
      for(int x : adj[u]){
        edge e = edges[x];
        if(e.cap-e.flow <= 0 || lv[e.v] != -1) continue;
        lv[e.v] = lv[u]+1;
        q.push(e.v);
      }
    }
    return lv[T] != -1;
  }

  ll dfs(int u, ll pushed){
    if(pushed == 0) return 0LL;
    if(u == T) return pushed;
    for(int& cid = ptr[u]; cid < (int)adj[u].size() ; ++cid){
      int id = adj[u][cid];
      edge e = edges[id];
      if(lv[u]+1 != lv[e.v] || e.cap-e.flow <= 0) continue;
      ll f = dfs(e.v, min(pushed, e.cap-e.flow));
      if(f == 0) continue;
      edges[id].flow += f;
      edges[id^1].flow -= f;
      return f;
    }
    return 0LL;
  }
  ll maxflow(){
    ll flow = 0LL;
    while(1){
      if(!bfs()) break;
      ptr.assign(N+5, 0);
      while(ll f = dfs(S, ooLL)){
        flow += f;
      }
    }
    return flow;
  }
};

int main(){
  int N, M;
  cin >> N >> M;
  Dinic D(1,N,N);
  for(int i = 0; i < M ; ++i){
    int a, b;
    ll c;
    cin >> a >> b >> c;
    D.add_edge(a,b,c);
  }

  cout << D.maxflow() << '\n';
  return 0;
}
