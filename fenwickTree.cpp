//FenwickTree algorithm
//Used for answer prefix sums querys and update values both in O(logN) time complexity
//For building the tree is O(NlogN) time complexity
#include <bits/stdc++.h>
using namespace std;

struct FenwickTree{
    vector<int> tree; //vector to represent our fenwick
    int N; //number of elements
    FenwickTree(const int n){ //just resizing the vector to N+1 position, because this fenwick tree is 1-indexed (1..N)
        N = n;
        tree.assign(n+1, 0);
    }
    //idx & (-idx) is the least significant bit
    void update(int idx, int val){ //increases the value at index idx in val units  //takes O(logN) time complexity
        idx++; //increasing one unit because our original vector is 0-indexed (0..N-1), so the idx would be 0
        while(idx <= N){
            tree[idx] += val;
            idx += idx & (-idx); //moving up in the tree
        }
    }

    int get(int idx){ //get the accumulated sum up to index idx   //takes O(logN) time complexity
        idx++; //increasing one unit because our original vector is 0-indexed (0..N-1), so the idx would be 0
        int sum = 0;
        while(idx>0){
            sum += tree[idx];
            idx -= idx & (-idx); //moving down in the tree
        }
        return sum;
    }

    void build(vector<int>& v){ //O(NlogN)
        for(int i = 0; i < (int)v.size() ; ++i) update(i,v[i]);
    }
};


int main(){
    vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    const int N =(int)v.size();
    FenwickTree tree(N);
    tree.build(v); //building the tree based on this vector v
    int a, b;
    while(scanf("%d%d", &a, &b) != EOF){
        if(a == 1) printf("%d\n", tree.get(b));
        else {
            int newVal;
            scanf("%d", &newVal);
            tree.update(b,newVal);
        }
    }

    return 0;
}
