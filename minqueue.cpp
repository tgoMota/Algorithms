//Queue keeping the minimum element
//All the operations in O(1) time complexity (push, pop, getMinimum)
#include <bits/stdc++.h>
using namespace std;
struct minqueue{
    deque<pair<int,int>> q;
    int cnt_pushed, cnt_popped;
    minqueue(){
        cnt_pushed = cnt_popped = 0;
    }
    void push(int new_element){
        while (!q.empty() && q.back().first > new_element) q.pop_back();
        q.push_back(make_pair(new_element, cnt_pushed));
        cnt_pushed++;
    }

    int getMin(){
        return q.front().first;
    }

    void pop(){
        if (!q.empty() && q.front().second == cnt_popped) q.pop_front();
        cnt_popped++;
    }
};

int main(){

    return 0;
}