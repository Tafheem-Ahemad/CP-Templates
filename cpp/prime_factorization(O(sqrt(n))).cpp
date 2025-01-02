

set<ll> find_primes(ll n){

	set<ll>st;
	for(ll i=2;i*i<=n;i++){
		while(n%i==0){
			st.in(i);
			n/=i;
		}
	}

	if(n>1) st.in(n);

	return st;
}