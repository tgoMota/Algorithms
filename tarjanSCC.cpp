//Tarjan's algorithm
//Algorithm to find all the Strongly Connected Components(SCC) on a Directed Graph
//Runs in O(V+E) time complexity
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
vector<int> dfs_num, dfs_low, vst, st;
vector<vector<ii>> adj;
vector<vector<int>> allscc; //save all the scc
void init(const int n){
    dfs_num.assign(n, 0);
    dfs_low.assign(n, 0);
    vst.assign(n, false);
    st.clear();
}
void tarjanSCC(int v, int& dfsCounter){
    dfs_num[v] = dfs_low[v] = ++dfsCounter;
    vst[v] = true;
    st.push_back(v);
    for(ii& x : adj[v]){ //x => {vertex, distance}
        int u = x.first;
        if(!dfs_num[u]) tarjanSCC(u, dfsCounter);
        if(vst[u]) dfs_low[v] = min(dfs_low[v], dfs_low[u]);
    }

    if(dfs_low[v] == dfs_num[v]){
        vector<int> new_scc;
        while(1){
            int t = st.back();
            st.pop_back();
            vst[t] = false;
            new_scc.push_back(t);
            if(t == v) break;
        }
        allscc.push_back(new_scc);
    }
}

void printSCC(){
    for(vector<int>& scc : allscc){
        for(int i = 0; i < (int)scc.size() ; ++i){
            if(i) printf(" ");
            printf("%d", scc[i]);
        }
        printf("\n");
    }
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    adj.assign(n, vector<ii>());
    for(int i = 0; i < m ; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        adj[a].push_back({b,c});
    }

    init(n);
    for(int i = 0, dfsCounter = 0; i < n ; ++i) {
        if(!dfs_num[i]) tarjanSCC(i, dfsCounter);
    }
    printSCC();

    return 0;
}