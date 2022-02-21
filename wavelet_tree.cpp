#include <bits/stdc++.h>
using namespace std;
#define oo 0x3f3f3f3f
#define ooLL 0x3f3f3f3f3f3f3f3f
#define fastio() ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0)
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
const int mod = 1e9+7;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> ii;
//CHECK THE CONSTRAINTS, PLEASE
typedef vector<int>::iterator it;
vector<int> v;
struct wavelet_tree{
  wavelet_tree *l, *r;
  int lo, hi;
  vector<int> pref;
  wavelet_tree(){};
  wavelet_tree(it left, it right, int x, int y){
    lo = x, hi = y;
    if(lo == hi) return;
    int mid = (lo + hi) >> 1;
    auto f = [mid](int x){
      return x <= mid;
    };
    pref.push_back(0);
    for(it i = left; i != right ; ++i){
      pref.push_back(pref.back() + f(*i));
    }

    auto pivot = stable_partition(left, right, f);
    l = new wavelet_tree(left, pivot, lo, mid);
    r = new wavelet_tree(pivot, right, mid+1, hi);
  };

  //count elements less or equal to x in [L,R]
  int LTE(int L, int R, const int x){
    if(L > R || x < lo) return 0;
    if(hi <= x) return R-L+1;
    int mid = (lo + hi) >> 1;
    return this->l->LTE(pref[L-1]+1, pref[R], x) + this->r->LTE(L-pref[L-1], R-pref[R], x);
  }

  //count elements equal to x in [L,R]
  int count(int L, int R, const int x){
    if(L > R || x < lo || x > hi) return 0;
    if(lo == hi) return R-L+1;
    int mid = (lo + hi) >> 1;
    if(x <= mid) return this->l->count(pref[L-1]+1, pref[R], x);
    return this->r->count(L-pref[L-1], R-pref[R], x);
  }
  
  //take the kth smallest element in [L,R]
  int kth(int L, int R, int k){
    if(L > R) return 0;
    if(lo == hi) return lo;
    int mid = (lo + hi) >> 1;
    int inLeft = pref[R]-pref[L-1];
    if(k <= inLeft) return this->l->kth(pref[L-1]+1, pref[R], k);
    return this->r->kth(L-pref[L-1], R-pref[R], k-inLeft);
  }

  ~wavelet_tree(){
	delete l;
	delete r;
   }
};
int main(){
  fastio();
  v = {0,7,2,3,4,1,7,7,8};
  wavelet_tree *wa = new wavelet_tree(v.begin()+1, v.end(), 1, *max_element(v.begin(), v.end()));
  int ansA = wa->count(1,8, 7);
  int ansB = wa->LTE(2,2, 5);
  int ansC = wa->kth(1,4, 3);
  trace(ansA, ansB, ansC);
  return 0;
}
