//Prim's algorithm
//Greedly algorith to find the Minimun Spanning Tree in a graph
//Runs in O(ELog(V)) time complexity.
//Prim's algorithm can be faster than Kruskral in dense graphs.
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
vector<vector<ii>> adj;
vector<bool> vst;
priority_queue<ii, vector<ii>, greater<ii>> pq;

void process(int v){
    vst[v] = true;
    for(ii x : adj[v]){
        if(!vst[x.first]) pq.push(x);
    }
}

int prim(const int N){
    vst.assign(N+1, false);
    process(0);
    int mst_cost = 0, cnt = 0;
    while(!pq.empty()){
        auto x = pq.top();
        pq.pop();
        int v = x.first;
        int w = x.second;
        if(vst[v]) continue;
        mst_cost+=w;
        if(++cnt == N-1) break;
        process(v);
    }
    return mst_cost;
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    adj.assign(n+1, vector<ii>());
    for(int i = 0; i < m ; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        adj[a].push_back({b,c});
    }

    int mst_cost = prim(n);
    printf("mst = %d\n", mst_cost);

    return 0;
}