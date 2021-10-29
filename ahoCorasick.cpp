//Aho-Corasick algorithm
//Build in O(M*K) which M is the sum of all lengths and K is the alphabet size
//Doing with hash, build in O(M)
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;

class Aho{ //Implementation with DFS online
    public:
        const static int K = 26;
        struct Node{
            int p, sz, suf_link = -1, out_link = -1;
            unordered_map<char,int> next, go;
            bool leaf = false;
            char ch;
            Node(int _p = -1, char _ch = '$', int _sz = 0){
                p = _p, ch = _ch, sz = _sz;
            };
        };
        vector<Node> trie;
        Aho(){
            trie.resize(1);
        };
        void add_string(string const& s){
            int v = 0;
            for(int i = 0; i < (int)s.size() ; ++i){
                int c = s[i]-'a';
                if(!trie[v].next.count(c)){
                    trie[v].next[c] = (int)trie.size();
                    trie.push_back(Node(v,s[i],i+1));
                }
                v = trie[v].next[c];
            }
            trie[v].leaf = true;
        }


        int get_suf_link(int v){
            if(trie[v].suf_link == -1){
                if(trie[v].sz <= 1) trie[v].suf_link = 0;
                else trie[v].suf_link = go(get_suf_link(trie[v].p), trie[v].ch);
            }
            return trie[v].suf_link;
        }

        int get_out_link(int v){
            if(trie[v].out_link == -1){
                if(trie[v].sz <= 1) trie[v].out_link = 0;
                else {
                    int suf_link = get_suf_link(v);
                    trie[v].out_link = trie[suf_link].leaf ? suf_link : get_out_link(suf_link);
                }
            }
            return trie[v].out_link;
        }

        int go(int v, char ch){
            int c = ch-'a';
            if(!trie[v].go.count(c)){
                if(trie[v].next.count(c)) trie[v].go[c] = trie[v].next[c];
                else trie[v].go[c] = v == 0 ? 0 : go(get_suf_link(v), ch);
            }
            return trie[v].go[c];
        }

        void get_match(int state, const int i, vector<ii>& _all_matchs){
            if(state == 0) return;
            if(trie[state].leaf) _all_matchs.push_back({i-trie[state].sz+1, i});
            get_match(get_out_link(state), i, _all_matchs);
        }

        vector<ii> all_matchs(string const& t){
            int state = 0;
            vector<ii> _all_matchs;
            for(int i = 0; i < (int)t.size() ; ++i){
                state = go(state, t[i]);
                get_match(state, i, _all_matchs);
            }

            return _all_matchs;
        }

        void print_matchs(string const& t){
            cout << "t = " << t << '\n';
            cout << "Matchs (";
            vector<ii> mat = all_matchs(t);
            cout << (int)mat.size() << "):\n";
            for(ii x : mat) cout << x.first << ' ' << x.second << '\n';
            cout << '\n';
        }

        void print_nodes(){
            cout << "nodes: \n";
            for(auto node : trie){
                cout << "p = " << node.p << ", ch = " << node.ch << ", suf_link = " << node.suf_link << ", leaf = " << node.leaf << '\n';
            }
            cout << '\n';
        }
};
//Implementation with BFS offline
struct Aho{
    vector<bool> out;  
    vector<int> f;
    vector<vector<int>> g; 
    int max_states, max_chars;
    char lowestChar, highestChar;
    Aho(){}
    Aho(const int _max_states, char _lowestChar = 'a', char _highestChar = 'z'){
      max_states = _max_states+5;
      out.assign(max_states, false);
      f.assign(max_states, -1);
      lowestChar = _lowestChar;
      highestChar = _highestChar;
      max_chars = highestChar-lowestChar+1;
      g.assign(max_states, vector<int>(max_chars, -1));
    }
    int build(const vector<string> &words) {
        int states = 1;   
        for (int i = 0; i < words.size(); ++i) {
            const string &keyword = words[i];
            int currentState = 0;
            for (int j = 0; j < (int)keyword.size(); ++j) {
                int c = keyword[j] - lowestChar;
                if(g[currentState][c] == -1) {
                    g[currentState][c] = states++;
                }
                currentState = g[currentState][c];
            }
            out[currentState] = true;
        }
        
        for (int c = 0; c < max_chars; ++c) {
            if (g[0][c] == -1) {
                g[0][c] = 0;
            }
        }
        queue<int> q;
        for (int c = 0; c < max_chars; ++c) {
            if (g[0][c] > 0) {
                f[g[0][c]] = 0;
                q.push(g[0][c]);
            }
        }
        while (!q.empty()) {
            int state = q.front();
            q.pop();
            for (int c = 0; c < max_chars; ++c) {
                if (g[state][c] != -1) {
                    int failure = f[state];
                    while (g[failure][c] == -1) {
                        failure = f[failure];
                    }
                    failure = g[failure][c];
                    f[g[state][c]] = failure;
                    out[g[state][c]] = out[g[state][c]] || out[failure];
                    q.push(g[state][c]);
                }
            }
        }

        return states;
    }
};

int main(){
    Aho aho;
    int n;
    cin >> n;
    for(int i = 0; i < n ; ++i){
        string s;
        cin >> s;
        aho.add_string(s);
    }
    string t;
    cin >> t;
    aho.print_matchs(t);
    aho.print_nodes();
    return 0;
}
