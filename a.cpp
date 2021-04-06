#include <bits/stdc++.h>
using namespace std;
#define LOCAL
#ifdef LOCAL
#define trace(...) __f(#__VA_ARGS__, __VA_ARGS__)
#else
#define trace(...) 42
#endif
template <typename Arg1>
void __f(const char* name, Arg1&& arg1){
  cerr << name << ": " << arg1 << endl;
}
template <typename Arg1, typename... Args>
void __f(const char* names, Arg1&& arg1, Args&&... args){
  const char* comma = strchr(names + 1, ',');
  cerr.write(names, comma - names) << ": " << arg1 << " |";
  __f(comma + 1, args...);
}
vector<int> sort_cyclic_shifts(string const& s) {
    int n = s.size();
    const int alphabet = 256;
    vector<int> p(n), c(n), cnt(max(alphabet, n), 0);
    for (int i = 0; i < n; i++)
        cnt[s[i]]++;
    for (int i = 1; i < alphabet; i++)
        cnt[i] += cnt[i-1]; //representa o rank de cada caractere
    // cout << "cnt: ";
    // for(int x : cnt) cout << x << " ";
    // cout << '\n';
    for (int i = 0; i < n; i++){
       // trace(s[i], cnt[s[i]], i);
        p[--cnt[s[i]]] = i; // p[i] representa a posicao do caractere em s que ocupa a i'nésima ordem lexicografica
    }
    c[p[0]] = 0;
    int classes = 1;
    for (int i = 1; i < n; i++) {
        if (s[p[i]] != s[p[i-1]])
            classes++;
        c[p[i]] = classes - 1;
    }
    // cout << "p: ";
    // for(int x : p) cout << x << " ";
    // cout << '\n';
    // cout << "c: ";
    // for(int x : c) cout << x << " ";
    // cout << '\n';
    vector<int> pn(n), cn(n);
    for (int h = 0; (1 << h) < n; ++h) {
        for(int i = 0; i < n ; ++i){
            trace(i, p[i], s[p[i]], s);
        }
        for (int i = 0; i < n; i++) {
            pn[i] = p[i] - (1 << h);
            if (pn[i] < 0)
                pn[i] += n;
            trace(i,pn[i], p[i], (1<<h), s[pn[i]], s[p[i]], s);
        }
        fill(cnt.begin(), cnt.begin() + classes, 0);
        for (int i = 0; i < n; i++){
            cnt[c[pn[i]]]++;
        }
        for (int i = 1; i < classes; i++)
            cnt[i] += cnt[i-1];
        for (int i = n-1; i >= 0; i--){
            p[--cnt[c[pn[i]]]] = pn[i];
        }
        cn[p[0]] = 0;
        classes = 1;
        for (int i = 1; i < n; i++) {
            pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << h)) % n]};
            pair<int, int> prev = {c[p[i-1]], c[(p[i-1] + (1 << h)) % n]};
            if (cur != prev)
                ++classes;
            cn[p[i]] = classes - 1;
        }
        c.swap(cn);
    }
    return p;
}

vector<int> suffix_array_construction(string s) {
    s += "$";
    trace(s);
    vector<int> sorted_shifts = sort_cyclic_shifts(s);
    sorted_shifts.erase(sorted_shifts.begin());
    return sorted_shifts;
}

int main(){
    const string s = "aaba";
   // trace(s);
    vector<int> r = suffix_array_construction(s);
    cout << "r: ";
    for(int x : r) cout << x << " ";
    cout << '\n';
    
    return 0;
}