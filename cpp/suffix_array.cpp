

#define ll long long int
#define pll pair<ll,ll>
#define vl vector<ll>

void count_sort(vector<pll> &b, ll bits) { // (optional)
	//this is just 3 times faster than stl sort for N=10^6
	ll mask = (1 << bits) - 1;
	for(ll it=0;it<2;it++) {
		ll move = it * bits;
		vl q(1 << bits), w(q.size() + 1);
		for(ll i=0;i<b.size();i++)
			q[(b[i].first >> move) & mask]++;
		partial_sum(q.begin(), q.end(), w.begin() + 1);
		vector<pll> res(b.size());
		for(ll i=0;i<b.size();i++)
			res[w[(b[i].first >> move) & mask]++] = b[i];
		swap(b, res);
	}
}
struct SuffixArray {
	vl a;
	string s;
	SuffixArray(const string& _s) : s(_s + '\0') {
		ll N = s.size();
		vector<pll> b(N);
		a.resize(N);
		for(ll i=0;i<N;i++) {
			b[i].first = s[i];
			b[i].second = i;
		}
 
		ll q = 8;
		while ((1 << q) < N) q++;
		for (ll moc = 0;; moc++) {
			count_sort(b, q); // sort(all(b)) can be used as well
			a[b[0].second] = 0;
			for(ll i=1;i<N;i++)
				a[b[i].second] = a[b[i - 1].second] +
					(b[i - 1].first != b[i].first);
 
			if ((1 << moc) >= N) break;
			for(ll i=0;i<N;i++) {
				b[i].first = (ll)a[i] << q;
				if (i + (1 << moc) < N)
					b[i].first += a[i + (1 << moc)];
				b[i].second = i;
			}
		}
		for(ll i=0;i<a.size();i++) a[i] = b[i].second;
	}
	ll lower_bound(string t){
		ll l = 1,r=a.size();
		while(l<r){
			ll m = (l+r)/2;
			if(s.substr(a[m],min((ll)s.size()-1-a[m],(ll)t.size()+1)) >= t) r = m;
			else l = m+1;
		}
		return l;
	}
	bool find(string &t) {
		ll l = 0, r = a.size() - 1;
		while (l <= r) {
			ll mid = (l + r) / 2;
			string suffix = s.substr(a[mid], min((ll)s.size() - a[mid], (ll)t.size()));
			if (suffix == t) {
				return 1;  
			} else if (suffix < t) {
				l = mid + 1;  
			} else {
				r = mid - 1; 
			}
		}
		return 0; 
	}
	ll upper_bound(string t){
		ll l = 1,r=a.size();
		while(l<r){
			ll m = (l+r)/2;
			if(s.substr(a[m],min((ll)s.size()-1-a[m],(ll)t.size())) > t) r = m;
			else l = m+1;
		}
		return l;
	}
	vl lcp() {
		// longest common prefixes: res[i] = lcp(a[i], a[i-1])
		ll n = a.size(), h = 0;
		vl inv(n), res(n);
		for(ll i=0;i<n;i++) inv[a[i]] = i;
		for(ll i=0;i<n;i++) if (inv[i] > 0) {
			int p0 = a[inv[i] - 1];
			while (s[i + h] == s[p0 + h]) h++;
			res[inv[i]] = h;
			if(h > 0) h--;
		}
		return res;
	}
};