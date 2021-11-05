struct mergeSortTree{
    int N;
    vector<vector<int>>tree;
    mergeSortTree(vector<int>&a){
        N = (int)a.size();
        tree.assign(4*N, vector<int>());
        build(0,0,N-1,a);
    }
    void build(int i, int l, int r, vector<int>&a){
        if(l == r){
            tree[i].push_back(a[l]);
            return;
        }
        int m = l + (r-l)/2;
        build(2*i+1, l, m, a );
        build(2*i+2, m+1, r, a );
        merge(all(tree[2*i+1]), all(tree[2*i+2]), back_inserter(tree[i]));
    }
    int query( int i, int l, int r, int ql, int qr, int hi){
        if(qr < l || ql > r) return 0;
        if(ql <= l && r <= qr) return (int)tree[i].size()-(lower_bound(all(tree[i]),hi)-tree[i].begin());
        int m = l + (r-l)/2;
        return query(2*i+1,l,m,ql,qr,hi) + query(2*i+2,m+1,r,ql,qr,hi);
    }
    int query(int l,int r, int val){ //how much in v[l,r] are greater or equal to val (>= val)
    	return query(0,0,N-1,l,r,val);
    }
};