#include<bits/stdc++.h>

// n=10^7
const int N  = 10000090;
int prime[N + 1];
void SieveOfEratosthenes()
{
    memset(prime, 0, sizeof(prime));
    prime[1]=-1;
    prime[0]=-1;
  
    for (ll p = 2; p * p <= N; p++) {
        if (prime[p] == 0) {
            for (ll i = p * p; i <= N; i += p)
                prime[i]++;
        }
    }
  
}   

// Print all prime numbers
// if(prime[i] == 0) then it is prime 
