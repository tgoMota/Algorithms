//Floyd Warshall algorithm
//This is a DP algorithm to calculate All-Pairs Shortest Paths and some variants.
//It's a slow algorithm, because it works clearly in O(V^3) time complexity, but can haldle negative edges
//and works well for small graphs (V<=~400) and it's simpler to code than the anothers algorithms.
#include <bits/stdc++.h>
using namespace std;
#define oo 0x3f3f3f3f
vector<vector<int>> dist;
void floydWarshall(const int N){
    for(int k = 0; k < N ; ++k){
        for(int i = 0; i < N ; ++i){
            for(int j = 0; j < N ; ++j){
                if(dist[i][k] == oo || dist[k][j] == oo) continue;
                dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
            }
        }
    }
}
int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    dist.assign(n+1, vector<int>(n+1, oo));
    for(int i = 0; i < m ; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        dist[a][b] = c;
    }
    int a, b;
    while(scanf("%d%d", &a, &b) != EOF){
        if(a < 0 || b < 0 || a >= n || b >= n) break;
        if(dist[a][b] == oo) printf("There is no path between %d and %d\n", a, b);
        else printf("dist[%d][%d] = %d\n", a, b, dist[a][b]);
    }

    return 0;
}
