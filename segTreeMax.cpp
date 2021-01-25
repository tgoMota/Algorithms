//Segment Tree Range Maximum Query
//This segment tree can answer range maximum querys and update values both in logN time complexity
#include <bits/stdc++.h>
using namespace std;
#define oo 0x3f3f3f3f
struct segMax{
    vector<int> t, v;
    segMax(const int n){
        t.assign(4*n, -oo);
    }
    void assign(vector<int>& x){ //takes the vector read on the main function
        v = x;
    }
    void build(int i, int l, int r){ //Construct the segment tree of //O(nlogn) time complexity
        if(l > r) return;
        if(l == r){ //leaf node
            t[i] = v[l];
        }else{
            int m = l + (r-l)/2; //similar to (l+r)/2, but can avoid overflow
            build(2*i, l, m);
            build(2*i+1, m+1, r);
            t[i] = max(t[2*i], t[2*i+1]);
        }
    }

    void update(int i, int l, int r, int p, int x){ //Change the value of v[p] to x //O(logn) time complexity
        if(l > r) return;
        if(l == r){
            t[i] = v[l] = x;
            return;
        }
        int m = l + (r-l)/2;
        if(p <= m) update(2*i, l, m, p, x);
        else update(2*i+1, m+1, r, p, x);
        t[i] = max(t[2*i], t[2*i+1]);
    }

    int query(int i, int l, int r, int ql, int qr){ //Maximum element between [ql,qr] //O(logn) time complexity
        if(ql <= l && qr >= r) return t[i];
        if(ql > r || qr < l) return -oo;
        int m = l + (r-l)/2;
        return max(query(2*i, l, m, ql, qr), query(2*i+1, m+1, r, ql, qr));
    }
};

int main(){
    vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    const int n = (int)v.size();
    segMax seg(n);
    seg.assign(v);
    seg.build(1,0,n-1);
    for(int i = 0, j = n-1; i < j ; ++i, --j){
    	printf("max([%d,%d]) : %d\n", i, j, seg.query(1,0,n-1, i,j));
    }
    return 0;
}
