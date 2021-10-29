//Kruskal’s algorithm
//Greedy algorithm for finding the Minimal Spanning Tree(MST) and some variants.
//This algorithm runs in O(ELog(E)) (or O(ELog(V))) time complexity, once E can be at most V^2.
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
vector<pair<int,ii>> edges;
vector<int> parent;

void buildUF(const int N){
    parent.resize(N);
    for(int i = 0; i < N ; ++i) parent[i] = i;
}

int find(int u){
    if(parent[u] == u) return u;
    return parent[u] = find(parent[u]); 
}

void merge(int u, int v){
    u = find(u), v = find(v);
    parent[u] = v;
}

bool isSameSet(int u, int v){
    return find(u) == find(v);
}

int kruskral(const int N){
    buildUF(N+1);
    sort(edges.begin(), edges.end());
    int mst = 0, cnt = 0;
    for(auto e : edges){
        int w = e.first;
        int u = e.second.first;
        int v = e.second.second;
        if(isSameSet(u,v)) continue;
        mst += w;
        merge(u,v);        
        if(++cnt == N-1) break;
    }
    return mst;
}

int main(){
    int n,m;
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m ; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        edges.push_back({c,{a,b}});
    }

    int mst = kruskral(n);
    printf("mst = %d\n", mst);
    return 0;
}
