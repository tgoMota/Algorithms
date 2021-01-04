//Dijkstra's algorithm
//Algorithm to find the shortest path between two nodes in a graph, but this algo can't handle negative edges
//Runs in O(ELog(V)) time complexity
#include <bits/stdc++.h>
using namespace std;
#define oo 0x3f3f3f3f
typedef pair<int,int> ii;
vector<vector<ii>> adj;
vector<int> dist;

void dijkstra(int source, const int n){
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push({0,source});
    dist.assign(n+1, oo);
    dist[source] = 0;
    while(!pq.empty()){
        auto x = pq.top();
        pq.pop();
        int v = x.second;
        for(auto a : adj[v]){
            int u = a.first, w = a.second;
            if(dist[v]+w < dist[u]){
                dist[u] = dist[v]+w;
                pq.push({dist[u], u});
            }
        }
    }
}

int main(){
    int n, m, source;
    scanf("%d%d%d", &n, &m, &source);
    adj.assign(n+1, vector<ii>());
    for(int i = 0; i < m ; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        adj[a].push_back({b,c});
    }

    dijkstra(source,n);
    for(int destiny = 0; destiny < n ; ++destiny){
        if(dist[destiny] >= oo) printf("No path between %d and %d\n", source, destiny);
        else printf("dist[%d] = %d\n", destiny, dist[destiny]);
    }
    
    return 0;
}