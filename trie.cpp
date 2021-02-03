//Trie data structure
//Insert, search and remove run in ~ O(N) time complexity, where N = string length
//The space complexity is O(N*M), where N is the number of strings and M is the biggest string on the Tries
#include <bits/stdc++.h>
using namespace std;
struct Node{
    bool end;
    unordered_map<char, Node*> m;
    Node(){
        end = false;
    }
};

struct Trie{
    Node *root;
    Trie(){
        root = new Node();
    }

    void insert(string s){
        Node* cur = root;
        const int N = (int)s.size();
        for(int i = 0; i < N ; ++i){
            auto it = cur->m.find(s[i]);
            if(it == cur->m.end()){
                Node *nw = new Node();
                cur->m[s[i]] = nw;
                cur = nw;
            }else{
                cur = it->second;
            }
        }
        cur->end = true;
    }

    bool search(string s){
        Node* cur = root;
        const int N = (int)s.size();
        for(int i = 0; i < N ; ++i){
            auto it = cur->m.find(s[i]);
            if(it == cur->m.end()) return false;
            cur = it->second;
        }
        return cur->end;
    }

    void remove(string s){
        return (void) remove_aux(root, s, 0, (int)s.size());
    }

    bool remove_aux(Node* node, string& s, int idx, const int N){
        if(idx == N){
            if(node->m.empty() && node->end) return true;
            return node->end = false;
        }
        auto it = node->m.find(s[idx]);
        if(it == node->m.end()) return false;
        
        bool can_remove = remove_aux(it->second, s, idx+1, N);
        if(!can_remove) return false;
        delete it->second;
        node->m.erase(it);
        return node->m.empty() && !node->end;
    }

    bool empty(){
        return root->m.empty();
    }
};

int main(){
    Trie* t = new Trie();
    t->insert("T");
    t->insert("Testing");
    t->insert("TestingHard");
    t->insert("TestingOMG");
    cout << t->search("T") << ' '; //1
    cout << t->search("Testing") << ' '; //1
    cout << t->search("TestingHard") << ' '; //1
    cout << t->search("TestingOMG") << '\n'; //1
    t->remove("T");
    cout << t->search("T") << ' '; //0
    cout << t->search("Testing") << ' '; //1
    cout << t->search("TestingHard") << ' '; //1
    cout << t->search("TestingOMG") << '\n'; //1
    t->remove("Testing");
    cout << t->search("T") << ' '; //0
    cout << t->search("Testing") << ' ';//0
    cout << t->search("TestingHard") << ' ';//1
    cout << t->search("TestingOMG") << '\n';//1
    t->remove("TestingHard");
    cout << t->search("T") << ' ';//0
    cout << t->search("Testing") << ' ';//0
    cout << t->search("TestingHard") << ' ';//0
    cout << t->search("TestingOMG") << '\n';//1
    t->remove("TestingOMG");
    cout << t->search("T") << ' ';//0
    cout << t->search("Testing") << ' ';//0
    cout << t->search("TestingHard") << ' ';//0
    cout << t->search("TestingOMG") << '\n';//0
    if(t->empty()) cout << "Trie is empty\n";
    else cout << "Trie is not empty\n";
    return 0;
}