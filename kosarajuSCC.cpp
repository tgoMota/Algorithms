//Kosaraju’s Algorithm
//This algorithm is used to find the Strongly Connected Components (SCCs) of a directed graph.
//Kosaraju's runs in O(2(V+E)) =>~ O(V+E) time complexity
#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj1, adj2, components;
vector<bool> vst;
stack<int> st;

void dfs1(int v){
    vst[v] = true;
    for(int x : adj1[v]){
        if(vst[x]) continue;
        dfs1(x);
    }
    st.push(v);
}

void dfs2(int v){
    vst[v] = true;
    components.back().push_back(v);
    for(int x : adj2[v]){
        if(vst[x]) continue;
        dfs2(x);
    }
}

void kosajaru(){
    const int N = (int)adj1.size();
    vst.assign(N+1, false);
    for(int i = 0; i < N ; ++i){
        if(vst[i]) continue;
        dfs1(i);
    }
    components.clear();
    vst.assign(N+1, false);
    while(!st.empty()){
        int v = st.top();
        st.pop();
        if(vst[v]) continue;
        components.push_back(vector<int>());
        dfs2(v);
    }
}

void printSCC(){
    printf("%d components found\n", (int)components.size());
    for(auto& x: components){
        for(int i = 0; i < (int)x.size() ; ++i){
            if(i) printf(" ");
            printf("%d", x[i]);
        }
        printf("\n");
    }
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    adj1.assign(n, vector<int>()); //adjacency list to the original graph
    adj2.assign(n, vector<int>()); //adjacency list to the transposed graph
    for(int i = 0; i < m ; ++i){
        int a, b;
        scanf("%d%d", &a, &b);
        adj1[a].push_back(b); //original graph
        adj2[b].push_back(a); //transposing graph
    }

    kosajaru();
    printSCC();
    return 0;
}
