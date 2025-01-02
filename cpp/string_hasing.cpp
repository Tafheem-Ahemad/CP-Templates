
// String Hashing Function a/c to Ploynomial change 

class StringHash {
public:
    vector<long long>ps1;
    vector<long long>powxyq1;
    long long Q1 = 271, M1 = 998244353;
    StringHash(string s) {
        ps1 = vector<long long>(s.size()+3); 
        powxyq1 = vector<long long>(s.size()+3); 
		powxyq1[0]=1;
        for (int i = 1; i <= s.size(); i++) {
            long long c = s[i-1] + 1;
            ps1[i] = ((Q1 * ps1[i-1]) + c)%M1;
			powxyq1[i]=(powxyq1[i-1]*Q1)%M1;
        }
    }

    long long substrHash(int firstIndex, int lastIndex) {
        long long rem = (powxyq1[lastIndex-firstIndex+1] * ps1[firstIndex])%M1;
        return (ps1[lastIndex+1] - rem + M1)%M1;
    }

    long long addTwoSubstring(long long a, long long b,long long sizeOfSecondString) {
        long long x=((a*powxyq1[sizeOfSecondString])%M1 + b)%M1;
        return x;
    }
};
