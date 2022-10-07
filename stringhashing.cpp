#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll compute_hash(string const& s) {
    const int p = 31;
    const int m = 1e9 + 9;
    ll hash_value = 0, p_pow = 1;
    for (int i = 0; i < (int)s.size() ; ++i) {
        char c = s[i];
        hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
        p_pow = (p_pow * p) % m;
    }
    return hash_value;
}