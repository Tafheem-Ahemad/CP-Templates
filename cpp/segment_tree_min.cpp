#include<bits/stdc++.h>
#define pp pair<ll,ll>
#define ll long long
#define fast() ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;


class node{
	public :
	ll mn;

	node(){
		mn=1e18;
	}
};

class SegmentTree {
public:
	vector<ll> arr;
	vector<node> seg;

	ll n;

	SegmentTree(vector<ll> v) {
        n=v.size();
        arr=v;
		seg.resize(4 * n + 1);
        build(0,0,n-1);
	}

	node merge(node a,node b){
		node ans;
		ans.mn=min(a.mn,b.mn);
		return ans;
	}
	void build(ll ind, ll low, ll high) {
		if (low == high) {
			seg[ind].mn = arr[low];
			return;
		}

		ll mid = (low + high) / 2;
		build(2 * ind + 1, low, mid);
		build(2 * ind + 2, mid + 1, high);
		seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
	}

	node query(ll ind, ll low, ll high, ll l, ll r) {
		// no overlap
		// l r low high or low high l r
		if (r < low || high < l) return node();

		// complete overlap
		// [l low high r]
		if (low >= l && high <= r) return seg[ind];

		ll mid = (low + high) >> 1;
		node left = query(2 * ind + 1, low, mid, l, r);
		node right = query(2 * ind + 2, mid + 1, high, l, r);
		return merge(left, right);
	}

	void update(ll ind, ll low, ll high, ll i, ll val) {
		if (low == high) {
			seg[ind].mn = val;
			return;
		}

		ll mid = (low + high) >> 1;
		if (i <= mid) update(2 * ind + 1, low, mid, i, val);
		else update(2 * ind + 2, mid + 1, high, i, val);
		seg[ind] = merge(seg[2 * ind + 1], seg[2 * ind + 2]);
	}
};


class SegmentTreeMin {
public:
	vector<ll> arr;
	vector<ll> seg;
	ll n;

	SegmentTreeMin(vector<ll>v) {
		ll n=v.size();
		arr=v;
		seg.resize(4 * n + 1);
		build(0,0,n-1);
	}

	void build(ll ind, ll low, ll high) {
		if (low == high) {
			seg[ind] = arr[low];
			return;
		}

		ll mid = (low + high) / 2;
		build(2 * ind + 1, low, mid);
		build(2 * ind + 2, mid + 1, high);
		seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
	}

	ll query(ll ind, ll low, ll high, ll l, ll r) {
		// no overlap
		// l r low high or low high l r
		if (r < low || high < l) return 1e18;


		if (low >= l && high <= r) return seg[ind];

		ll mid = (low + high) >> 1;
		ll left = query(2 * ind + 1, low, mid, l, r);
		ll right = query(2 * ind + 2, mid + 1, high, l, r);
		return min(left, right);
	}


	void update(ll ind, ll low, ll high, ll i, ll val) {
		if (low == high) {
			seg[ind] = val;
			return;
		}

		ll mid = (low + high) >> 1;
		if (i <= mid) update(2 * ind + 1, low, mid, i, val);
		else update(2 * ind + 2, mid + 1, high, i, val);
		seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
	}
};



int main(){
	fast();

	ll n;
	cin>>n;

	vector<ll>v(n);
	for(ll i=0;i<n;i++) cin>>v[i];

	SegmentTree s1(v);

	ll q;
	cin>>q;
	while(q--){
		ll type;
		cin>>type;

		if(type==1){
			ll l,r;
			cin>>l>>r;
			node ans=s1.query(0,0,n-1,l,r);
			cout<<ans.mn<<endl;
		}else{
			ll i, val;
			cin>>i>>val;
			s1.update(0,0,n-1,i,val);
		}
	}

	return 0;
}