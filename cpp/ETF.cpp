
// Euler Toitent Fuction

ll ETF(ll n){
    ll ans=n;
        
    for(ll i=2;i*i<=n;i++){
        if(n%i==0){
            ans/=i;
            ans*=(i-1);
            
            while(n%i==0) n/=i;
        }
    }
        
    if(n>1){
        ans/=n;
        ans*=(n-1);
    }
        
    return ans;
}