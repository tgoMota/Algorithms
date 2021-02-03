//Greatest Common Divisor & Least Common Multiple
//Both works in O(logn), where n = max(a, b).
#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b){ //Euclid algorithm
    return b == 0 ? a : gcd(b, a%b);
}

int lcm(int a, int b){
    return a*(b/gcd(a,b));
}
