#define ll long long

// Decimal to string fuction

string to_decimal(ll n){

    string s(62,'0');
    for(int i=0;i<62;i++){
        if(n>>i & 1ll) s[62-i-1]='1';
    }

    return s;
}