//Kahn’s algorithm for Topological Sorting
//Algorithm to find Topological sorting of a Directed Acyclic Graph (DAG) using BFS
//Runs in O(V+E) time complexity
#include <bits/stdc++.h>
using namespace std;
vector<int> topSort, in_degree;
vector<vector<int>> adj;

int topologicalSort(const int n){
    topSort.clear();
    queue<int> q;
    for(int i = 0; i < n ; ++i){
        if(in_degree[i] == 0) q.push(i);
    }
    int cnt = 0;
    while(!q.empty()){
        int v = q.front();
        q.pop();
        cnt++;
        topSort.push_back(v);
        for(int x : adj[v]){
            if(--in_degree[x] == 0) q.push(x);
        }
    }
    if(cnt != n){
        printf("There is a cycle in the given graph\n");
        return 0;
    }

    printf("Topological sort:");
    for(int x : topSort) printf(" %d", x);
    printf("\n");
    return 1;
}

int main(){
    int n, m;
    while(scanf("%d%d", &n, &m) != EOF){
        adj.assign(n+1, vector<int>());
        in_degree.assign(n+1, 0);
        for(int i = 0; i < m ; ++i){
            int a, b;
            scanf("%d%d", &a, &b);
            adj[a].push_back(b);
            in_degree[b]++;
        }

        topologicalSort(n);
    }

    return 0;
}
