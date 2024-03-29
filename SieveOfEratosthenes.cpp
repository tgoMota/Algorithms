//Sieve of Eratosthenes Algorithm
//This Algorithm can generate a list of prime numbers between range [0..n]
//takes O(nlog(log(n))) time complexity 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<bool> prime;
vector<int> primes;
void sieve(ll _upto){
    primes.clear();
    _upto++;
    prime.assign(_upto+1, true);
    prime[0] = prime[1] = false;
    for(ll i = 2; i <= _upto ; ++i){
        if(prime[i]){
            for(ll j = i*i; j <= _upto ; j += i) prime[j] = 0;
            primes.push_back(i);
        }
    }
}
bool isPrime(int n){
    return prime[n];
}
int main(){
    const int n = 10000;
    sieve(n); //generate a list of primes up to n;
    printf("primes: ");
    for(int x : primes) printf("%d ", x);
    printf("\n");
    return 0;
}
