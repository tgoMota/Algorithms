#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int nax = 1e7 + 10;
int P[nax];
int head[nax], nxt[nax], to[nax], flow[nax], cost[nax];
bool M[nax];
ll D[nax];
struct MCMF{
    int s, t, ts;
    MCMF(int source, int sink){
        ts = 0;
        s = source;
        t = sink;
        memset(head, -1, sizeof(head));
        memset(nxt, -1, sizeof(nxt));
    }
    inline void add_edge(int v, int u, int w, int c){
        to[ts] = u; flow[ts] = w; cost[ts] = c;
        nxt[ts] = head[v]; head[v] = ts ++;
        to[ts] = v; flow[ts] = 0; cost[ts] = -c;
        nxt[ts] = head[u]; head[u] = ts ++;
    }
    inline bool SPFA(){
        queue <int> qu;
        memset(M, 0, sizeof(M));
        memset(P, -1, sizeof(P));
        memset(D, oo, sizeof(D));
        D[s] = 0; qu.push(s);
        while((int)qu.size()){
            int v = qu.front();
            qu.pop(); M[v] = 0;
            for(int id = head[v]; ~ id; id = nxt[id])
                if(flow[id] && D[to[id]] > D[v] + cost[id]){
                    P[to[id]] = id;
                    D[to[id]] = D[v] + cost[id];
                    if(!M[to[id]])
                        qu.push(to[id]), M[to[id]] = 1;
                }
        }
        return (P[t] != -1);
    }
    inline pair <int, ll > MaxFlow(){
        int Flow = 0;
        ll Cost = 0;
        while (SPFA()){
            int v = t, _flow = INT_MAX;
            while (v != s)
                _flow = min(_flow, flow[P[v]]), v = to[P[v]^1];
            Flow += _flow; Cost += _flow * D[t]; v = t;
            while (v != s){
                flow[P[v]] -= _flow;
                flow[P[v]^1] += _flow;
                v = to[P[v]^1];
            }
        }
        return make_pair(Flow, Cost);
    }
