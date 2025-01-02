#include<bits/stdc++.h>
#define ll long long
using namespace std;

string decimal_to_binary(ll n){

    string s(62,'0');
    for(int i=0;i<62;i++){
        if(n>>i & 1) s[61-i]='1';
    }

    return s;
}

long long binaryToDecimal(string binaryStr) {
    long long decimalNum = 0;
    int power = binaryStr.length() - 1;
    
    for (char digit : binaryStr) {
        if (digit == '1') {
            decimalNum += (1ll << power);
        }
        power--;
    }
    
    return decimalNum;
}