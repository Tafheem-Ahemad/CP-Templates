
// power of matrix

vector<vector<ll>> mul(vector<vector<ll>>&a,vector<vector<ll>>&b){
    vector<vector<ll>>ans(a.size(),vector<ll>(b[0].size(),0));
    
    for(int i=0;i<a.size();i++){
        for(int j=0;j<b[0].size();j++){
            for(int k=0;k<a[0].size();k++){
                ans[i][j]+=(a[i][k]%MOD)*(b[k][j]%MOD);
                ans[i][j]%=MOD;
            }
        }
    }
    
    return ans;
}

vector<vector<ll>> power(vector<vector<ll>>a,ll n){
    ll size=a.size();
    vector<vector<ll>>ans(size,vector<ll>(size,0));
    for(int i=0;i<size;i++) ans[i][i]=1;
    
    while(n>0){
        if(n%2){
            ans=mul(ans,a);
            n--;
        }else{
            a=mul(a,a);
            n/=2;
        }
    }
    
    return ans;
}