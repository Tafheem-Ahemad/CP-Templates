
// Prime Factorization in O(log n)

class prime_factorization{
    public:
    int MAXN;
    vector<int> spf;

    prime_factorization(int n){
        MAXN=n;
		spf.resize(MAXN+2);
		sieve();
    }

    void sieve()
    {
        for (ll i = 2; i <= MAXN; i++)
            spf[i] = i;
    
        // separately marking spf for every even
        // number as 2
        for (ll i = 4; i <= MAXN; i += 2)
            spf[i] = 2;
    
        for (ll i = 3; i * i <= MAXN; i++) {
            // checking if i is prime
            if (spf[i] == i) {
                // marking SPF for all numbers divisible by i
                for (ll j = i * i; j <= MAXN; j += i)
    
                    // marking spf[j] if it is not
                    // previously marked
                    if (spf[j] == j)
                        spf[j] = i;
            }
        }
    }

    vector<long long> getFactorization(long long x)
    {
        vector<long long> ret;
        while (x != 1) {
            ret.push_back(spf[x]);
            x = x / spf[x];
        }
        return ret;
    }
};


int main()
{
    // precalculating Smallest Prime Factor
    sieve();
    int x = 12246;
    cout << "prime factorization for " << x << " : ";
 
    // calling getFactorization function
    vector<int> p = getFactorization(x);
 
    for (int i = 0; i < p.size(); i++)
        cout << p[i] << " ";
    cout << endl;
    return 0;
}
