//Segment Tree with lazy propagation
//This segment tree can answer range sum querys and modify values in range both in logN time complexity
#include <bits/stdc++.h>
using namespace std;
struct SegTreeLazyProp{
    vector<int> t, lz;
    Seg(const int n){
        t.assign(4*n, 0);
        lz.assign(4*n, 0);
    }

    void push(int i, int l, int r){ //O(1)
        if(lz[i]){
            t[i] += lz[i] * (r-l+1);
            if(l != r){
                lz[2*i] += lz[i];
                lz[2*i+1] += lz[i];
            }
        }
        lz[i] = 0;
    }

    int query(int i, int l, int r, int ql, int qr){ //O(logN)
        push(i, l, r);
        if(r < ql || l > qr) return 0;
        if(ql <= l && qr >= r) return t[i];
        int m = (l+r)>>1;
        return query(2*i, l, m, ql, qr) + query(2*i+1, m+1, r, ql, qr);
    }

    void update(int i, int l, int r, int ql, int qr, int x){ //O(logN)
        push(i, l, r);
        if(r < ql || l > qr) return;
        if(ql <= l && qr >= r){
            lz[i] += x;
            push(i, l, r);
            return;
        }

        int m = (l+r)>>1;
        update(2*i, l, m, ql, qr, x);
        update(2*i+1, m+1, r, ql, qr, x);
        t[i] = t[2*i] + t[2*i+1];
    }
};
int main()[
    

    return 0;
]
