//Union find with path compression
struct UF{
  int N;
  vector<int> p;
  UF(const int n){
    N = n;
    p.resize(n+1);
    for(int i = 0; i <= n ; ++i) p[i] = i;
  }

  int find(int x){
    if(p[x] == x) return x;
    return p[x] = find(p[x]);
  }

  bool isSame(int u, int v){
    return find(u) == find(v);
  }

  void merge(int a, int b){
    p[find(a)] = find(b);
  }
};


//Union find with path compression by rank
struct UF{
  int N;
  vector<int> p, rnk;
  UF(const int n){
    N = n;
    p.resize(n+1);
    rnk.resize(n+1);
    for(int i = 0; i <= n ; ++i) p[i] = i, rnk[i] = 0;
  }
 
  int find(int x){
    if(p[x] == x) return x;
    return find(p[x]);
  }
 
  bool isSame(int u, int v){
    return find(u) == find(v);
  }
 
  void merge(int a, int b){
    a = find(a);
    b = find(b);
    if(rnk[a] < rnk[b]) p[a] = b;
    else if(rnk[a] > rnk[b]) p[b] = a;
    else{
      p[b] = a;
      rnk[a]++;
    }
  }
};