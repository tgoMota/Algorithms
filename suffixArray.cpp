//Suffix array O(NlogN)
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

struct suffixArray{
    const int ALPHABET = 256;
    vector<int> SA, tempSA, RA, tempRA, c;
    vector<int> LCP, Phi, PLCP;
    string s;
    int N;
    suffixArray(){}
    suffixArray(string _s){
        s = _s + "$";
        N = (int)s.size();
        SA.assign(N, 0);
        RA.assign(N, 0);
        tempSA.assign(N, 0);
        tempRA.assign(N, 0);
        LCP.assign(N, 0);
        Phi.assign(N, 0);
        PLCP.assign(N, 0);
        buildSA();
        buildLCP();
        SA.erase(SA.begin());
        LCP.erase(LCP.begin());
    }

    void countingSort(int k){
        int maxc =  max(ALPHABET,N);
        c.assign(maxc, 0);
        for(int i = 0; i < N ; ++i) c[RA[(i+k)%N]]++;
        for(int i = 1; i < maxc ; ++i) c[i]+=c[i-1];
        for(int i = N-1 ; i >= 0 ; --i) tempSA[--c[RA[(SA[i]+k)%N]]] = SA[i];
        SA.swap(tempSA);
    }

    void buildSA(){ //SA construction in O(NlogN) using radix sort
        for(int i = 0; i < N ; ++i) {
            SA[i] = i;
            RA[i] = s[i];
        }
        for(int k = 1; k < N ; k <<= 1){
            countingSort(k);
            countingSort(0);
            int r = tempRA[SA[0]] = 0;
            for(int i = 1; i < N ; ++i){
                tempRA[SA[i]] =  (ii(RA[SA[i]], RA[(SA[i]+k)%N]) == ii(RA[SA[i-1]], RA[(SA[i-1]+k)%N]) ? r : ++r);
            }
            RA.swap(tempRA);
            if(RA[SA[N-1]] == N-1) break;
        }
    }

    void buildLCP(){ //Longest Common Prefix in O(N)
        Phi[SA[0]] = -1;
        for(int i = 1; i < N ; ++i) Phi[SA[i]] = SA[i-1];
        for(int i = 0, k = 0; i < N ; ++i){
            if(Phi[i] == -1){
                PLCP[i] = 0;
                continue;
            }
            while(s[i+k] == s[Phi[i]+k]) ++k;
            PLCP[i] = k;
            k = max(k-1,0);
        }
        for(int i = 0; i < N ; ++i) LCP[i] = PLCP[SA[i]];
    }

    void printSA(){
        cout << "SA: ";
        for(int i = 0; i < N ; ++i) cout << SA[i] << ' ';
        cout << '\n';
    }
};

int main(){
    int t;
    cin >> t;
    while(t--){
        string line;
        cin >> line;
        suffixArray SA(line);
        SA.printSA();
    }
    
    return 0;
}
