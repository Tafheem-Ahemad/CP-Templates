
#include<bits/stdc++.h>
using namespace std;

#define ll long long int
const int N=2*1e6;

// https://www.geeksforgeeks.org/queries-of-ncrp-in-o1-time-complexity/
// Template taken from geeksforgeeks

// array to store inverse of 1 to N 
ll  factorialNumInverse[N + 1]; 
  
// array to precompute inverse of 1! to N! 
ll  naturalNumInverse[N + 1]; 
  
// array to store factorial of first N numbers 
ll  fact[N + 1]; 
  
// Function to precompute inverse of numbers 
void InverseofNumber(ll  p=MOD,ll x=N) 
{ 
    naturalNumInverse[0] = naturalNumInverse[1] = 1; 
    for (ll i = 2; i <= x; i++) 
        naturalNumInverse[i] = naturalNumInverse[p % i] * (p - p / i) % p; 
} 
// Function to precompute inverse of factorials 
void InverseofFactorial(ll  p=MOD,ll x=N) 
{ 
    factorialNumInverse[0] = factorialNumInverse[1] = 1; 
  
    // precompute inverse of natural numbers 
    for (ll i = 2; i <= N; i++) 
    factorialNumInverse[i] = (naturalNumInverse[i] * factorialNumInverse[i - 1]) % p; 
} 
  
// Function to calculate factorial of 1 to N 
void factorial(ll  p=MOD,ll x=N) 
{ 
    fact[0] = 1; 
  
    // precompute factorials 
    for (ll i = 1; i <= x; i++) { 
        fact[i] = (fact[i - 1] * i) % p; 
    } 
} 
  
// Function to return nCr % p in O(1) time 
ll  Binomial(ll  n, ll  r,ll  p=MOD) 
{ 
    // n C r = n!*inverse(r!)*inverse((n-r)!)
    if(r==0) return 1ll;
    if(r<0) return 0ll; 
	if(n==r) return 1ll;
	if(n<r) return 0ll;
    ll  ans = ((fact[n] * factorialNumInverse[r]) 
              % p * factorialNumInverse[n - r]) 
             % p; 

    return ans; 
}



int main(){
	fast();

	InverseofNumber(MOD); 
    InverseofFactorial(MOD); 
    factorial(MOD); 

	ll t=1;
	cin>>t;
	for(ll o=1;o<=t;o++){
		Ahemad();
		//cout<<"case : "<<o<<endl;
	}
	return 0;
}