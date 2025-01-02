
// 1 based indexing 

ll count_set_bits_from_0_to_n(ll n,ll bit){
	ll sum=0;
	ll a=(1ll<<bit);
 
	ll z=n/a;
	sum+=(a/2)*z;
 
	ll p=n%a;
	p++;
 
	if(p>(a/2)) sum+=p-(a/2);

	return sum;
}
