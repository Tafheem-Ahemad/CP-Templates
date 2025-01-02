#include<iostream>
#include<bits/stdc++.h>
#define pp pair<int,int>
#define ll long long
#define fast() ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;

// String Hashing , in one String different part

class StringHash {
public:
    vector<long long>ps1,ps2;
    vector<long long>powxyq1,powxyq2;
    long long Q1 = 277, Q2 = 271, M1 = 1000000007, M2 = 998244353;
    StringHash(string s) {
        ps1 = vector<long long>(s.size()+3); ps2 = vector<long long>(s.size()+3);
        powxyq1 = vector<long long>(s.size()+3); powxyq2 = vector<long long>(s.size()+3);
		powxyq1[0]=powxyq2[0]=1;
        for (int i = 1; i <= s.size(); i++) {
            long long c = s[i-1] + 1;
            ps1[i] = ((Q1 * ps1[i-1]) + c)%M1;
            ps2[i] = ((Q2 * ps2[i-1]) + c)%M2;
			powxyq1[i]=(powxyq1[i-1]*Q1)%M1;
			powxyq2[i]=(powxyq2[i-1]*Q2)%M2;
        }
    }

    long long substrHash1(int firstIndex, int lastIndex) {
        long long rem = (powxyq1[lastIndex-firstIndex+1] * ps1[firstIndex])%M1;
        return (ps1[lastIndex+1] - rem + M1)%M1;
    }
    long long substrHash2(int firstIndex, int lastIndex) {
        long long rem = (powxyq2[lastIndex-firstIndex+1] * ps2[firstIndex])%M2;
        return (ps2[lastIndex+1] - rem + M2)%M2;
    }
    pair<long long, long long> substrHash(int firstIndex, int lastIndex) {
        return {substrHash1(firstIndex, lastIndex), substrHash2(firstIndex, lastIndex)};
    }


	pair<long long, long long> addTwoSubstring(pair<long long,long long> a, pair<long long,long long>b,long long sizeOfSecondString) {
        long long x=((a.first*powxyq1[sizeOfSecondString])%M1 + b.first)%M1;
        long long y=((a.second*powxyq2[sizeOfSecondString])%M2 + b.second)%M2;
        return {x,y};
    }

	pair<long long, long long> addTwoSubstring (int i1,int j1,int i2,int j2){
		pair<long long, long long> a=substrHash(i1,j1);
		pair<long long, long long> b=substrHash(i2,j2);
		long long sizeOfSecondString=j2-i2+1;
		long long x=((a.first*powxyq1[sizeOfSecondString])%M1 + b.first)%M1;
        long long y=((a.second*powxyq2[sizeOfSecondString])%M2 + b.second)%M2;
        return {x,y};
	}
};


int main(){
	fast();

	string s="aaaaaa";
	StringHash hash(s);

	cout<<(hash.substrHash(0,1) == hash.substrHash(1,2))<<endl;
	cout<<(hash.substrHash(0,1) == hash.substrHash(0,2))<<endl;

	return 0;
}



// Practice Problem: 
// https://codeforces.com/contest/1539/problem/D