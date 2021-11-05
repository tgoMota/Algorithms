#include <bits/stdc++.h>
using namespace std;
struct kmp{
    string pat;
    vector<int> tmp;
    kmp(string _pattern){
        pat = _pattern;
        build();
    }
    void build(){
        const int N = (int)pat.size();
        tmp.assign(N+1, 0); //abababtab
        tmp[0] = -1;
        int i = 0, j = -1;
        while(i < N){
            while(j >= 0 && pat[i] != pat[j]) j = tmp[j];
            ++i, ++j;
            tmp[i] = j;
        }
    }

    int count(string str){
        const int N = (int)str.size();
        const int M = (int)pat.size();
        int i = 0, j = 0;
        int ans = 0;
        while(i < N){
            while(j>=0 && pat[j] != str[i]) j = tmp[j];
            i++, j++;
            if(j == M){
                ans++;
                j = tmp[j];
            }
        }
        return ans;
    }
};
