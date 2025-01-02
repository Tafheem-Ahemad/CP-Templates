
#define ll long long int
// Power Function

ll power(ll a,ll n , ll mod=MOD){
	a%=mod;
    ll res=1;
    while(n){
        if(n%2){
            res=res*a;
			res%=mod;
            n--;
        }else{
            a=(a*a);
			a%=mod;
            n/=2;
        }
    }
    
    return res;
}

ll inverse(ll n,ll m=MOD){
	return power(n,m-2,m);
}

ll power(ll x, ll n, ll m) {
	assert(n >= 0);
	x %= m;
	ll res = 1;
	while (n > 0) {
		if (n % 2 == 1) {  
			res = (res * x) % m;
		}
		x = (x * x) % m;
		n /= 2;
	}
	return res;
}
