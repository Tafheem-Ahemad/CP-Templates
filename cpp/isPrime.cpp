#include<bits/stdc++.h>

bool isPrime(ll n){
	if(n==1) return 0;

	ll p=sqrt(n);
	if(p*p == n) return 0;
	for(ll i=2;i<=p;i++){
		if(n%i == 0) return 0;
	}

	return 1;
}