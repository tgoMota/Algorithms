//Finding the modular multiplicative inverse
#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
//Euclidean Algorithm
int gcdExtended(int a, int b, int& x, int& y){
    if (a == 0){
        x = 0, y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

//Modular multiplicative inverse
int modInverse(int a, int m){
    int x, y;
    int g = gcdExtended(a, m, x, y);
    if (g != 1) return -1; //Inverse doesn't exist
    int ans = (x % m + m) % m;
    return ans;
}

int main(){
    int num = 2;
    cout << modInverse(num,mod) << '\n';
    return 0;
}