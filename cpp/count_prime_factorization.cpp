
// count prime factorization

const int N  = 1000009;
int prime[N + 2]={0};

vl primes;

void SieveOfEratosthenes()
{
    prime[1]=-1;
    prime[0]=-1;
    memset(prime, 0, sizeof(prime));
  
    for (int p = 2; p * p <= N; p++) {
        if (prime[p] == 0) {
            for (int i = p * p; i <= N; i += p)
                prime[i]++;
        }
    }
  
	primes.clear();
	for(int i=2;i<=N;i++){
		if(prime[i]==0) primes.pb(i);
	}
}   


ll count_prime_factorization(ll n){

	ll a=0;
	for(auto i:primes){
		if(i*i > n) break;
		while(n%i==0){
			n/=i;
			a++;
		}
	}

	if(n>1) a++;

	return a;
}