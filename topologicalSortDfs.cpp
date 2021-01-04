//Algorithm to find Topological sorting of a Directed Acyclic Graph (DAG) using DFS
//Runs in O(V+E) time complexity
#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> adj;
vector<bool> vst;
stack<int> topOrder;

void dfsTopSort(int v){
    vst[v] = true;
    for(int x : adj[v]){
        if(vst[x]) continue;
        dfsTopSort(x);
    }
    topOrder.push(v);
}

int main(){
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF){
        adj.assign(n+1, vector<int>());
        for(int i = 0; i < m  ; ++i){
            int a, b;
            scanf("%d%d", &a, &b);
            adj[a].push_back(b);
        }

        vst.assign(n+1, false);
        for(int i = 0; i < n ; ++i){
            if(!vst[i]) dfsTopSort(i);
        }
        printf("Topological sort:");
        while(!topOrder.empty()){
            int x = topOrder.top();
            topOrder.pop();
            printf(" %d", x);
        }
        printf("\n");
    }
    
    return 0;
}
