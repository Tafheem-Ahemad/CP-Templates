#include<iostream>
#include<bits/stdc++.h>
#define pp pair<int,int>
#define ll long long
#define fast() ios_base::sync_with_stdio(false); cin.tie(NULL);
using namespace std;

class node{
	public :
	ll sum;
	ll lazy_add;
	ll lazy_set;

	node(){
		sum=0;
		lazy_add=0;
		lazy_set=0;
	}
};

class SegmentTree{
public :
	vector<ll> arr;
	vector<node> seg;
	int n;

	SegmentTree(vector<ll>v) {
		n=v.size();
		arr=v;
		seg.resize(4 * n+2); 
		build(0,0,n-1); 
	}

	node merge(node a,node b){
		node ans;
		ans.sum=a.sum+b.sum;
		return ans;
	}

	void build(int ind, int low, int high) {
		if(low == high) {
			seg[ind].sum = arr[low];
			return; 
		}

		int mid = (low + high) >> 1; 
		build(2*ind+1, low, mid); 
		build(2*ind+2, mid+1, high); 
		seg[ind] = merge(seg[2*ind+1] , seg[2*ind+2]);
	}

	void propagateDown(int cur,int child){
		if(seg[cur].lazy_set != 0){
			seg[child].lazy_set=seg[cur].lazy_set;
			seg[child].lazy_add=0;
		}else {
			if(seg[child].lazy_set != 0){
				seg[child].lazy_set+=seg[cur].lazy_add;
			}else{
				seg[child].lazy_add+=seg[cur].lazy_add;
			}
		}
	}

	void propagate(int ind,int low,int high){
		if(seg[ind].lazy_add == 0 && seg[ind].lazy_set==0) return ;

		if(low != high){
			propagateDown(ind,2*ind+1);
			propagateDown(ind,2*ind+2);
		}

		if(seg[ind].lazy_add != 0) {
			seg[ind].sum += (high - low + 1) * seg[ind].lazy_add;  
			seg[ind].lazy_add=0;
		}else if(seg[ind].lazy_set != 0){
			seg[ind].sum = (high - low + 1) * seg[ind].lazy_set;  
			seg[ind].lazy_set=0;
		}
	}
	void rangeIncrease(int ind, int low, int high, int l, int r, int val) {
		// update the previous remaining updates 
		// and propogate downwards 
		propagate(ind,low,high);
 
		// no overlap 
		// we don't do anything and return 
		// low high l r or l r low high 
		if(high < l or r < low) {
			return; 
		}
 
		// complete overlap 
		// l low high r 
		if(low>=l && high <= r) {
			seg[ind].lazy_add += val;
			propagate(ind,low,high);
			return; 
		}

		// last case has to be no overlap case
		int mid = (low + high) >> 1; 
		rangeIncrease(2*ind+1, low, mid, l, r, val);
		rangeIncrease(2*ind+2, mid+1, high, l, r, val); 
		seg[ind] = merge(seg[2*ind+1] , seg[2*ind+2]);
	}
	void rangeSet(int ind, int low, int high, int l, int r, int val) {
		// update the previous remaining updates 
		// and propogate downwards 
		propagate(ind,low,high);
 
		// no overlap 
		// we don't do anything and return 
		// low high l r or l r low high 
		if(high < l or r < low) {
			return; 
		}
 
		// complete overlap 
		// l low high r 
		if(low>=l && high <= r) {
			seg[ind].lazy_set = val;
			propagate(ind,low,high);
			return; 
		}

		// last case has to be no overlap case
		int mid = (low + high) >> 1; 
		rangeSet(2*ind+1, low, mid, l, r, val);
		rangeSet(2*ind+2, mid+1, high, l, r, val); 
		seg[ind] = merge(seg[2*ind+1] , seg[2*ind+2]);
	}

	ll query(int ind, int low, int high, int l, int r) {
 
		// update if any updates are remaining 
		// as the node will stay fresh and updated 
		propagate(ind,low,high);
 
		// no overlap return 0; 
		if(high < l or r < low) {
			return 0; 
		}
 
		// complete overlap 
		if(low>=l && high <= r) return seg[ind].sum; 
 
		int mid = (low + high) >> 1; 
		ll left = query(2*ind+1, low, mid, l, r);
		ll right = query(2*ind+2, mid+1, high, l, r);
		return (left+right); 
	}
};

class SegmentTreeMin {
public: 
	vector<ll> arr; 
	vector<ll> seg; 
	vector<ll> lazy; 
	int n;
	ll default_val=0;

	SegmentTreeMin(vector<ll>v) {
		n=v.size();
		arr=v;
		seg.resize(4 * n+1,default_val); 
		lazy.resize(4 * n+1,default_val); 
		build(0,0,n-1);
	}

	void propagate(int ind, int low, int high) {
		if(lazy[ind] != default_val) {
			seg[ind] += lazy[ind]; 
			// propogate the lazy update downwards
			// for the remaining nodes to get updated 
			if(low != high) {
				lazy[2*ind+1] += lazy[ind]; 
				lazy[2*ind+2] += lazy[ind]; 
			}
 
			lazy[ind] = default_val; 
		}
	}

	void build(int ind, int low, int high) {
		if(low == high) {
			seg[ind] = arr[low];
			return; 
		}
		int mid = (low + high) >> 1; 
		build(2*ind+1, low, mid); 
		build(2*ind+2, mid+1, high); 
		seg[ind] = min(seg[2*ind+1], seg[2*ind+2]);
	}

	void update(int ind, int low, int high, int l, int r, ll val) {
		// update the previous remaining updates 
		// and propogate downwards 
		propagate(ind,low,high);
 
		// no overlap 
		// we don't do anything and return 
		// low high l r or l r low high 
		if(high < l or r < low) {
			return; 
		}
 
		// complete overlap 
		// l low high r 
		if(low>=l && high <= r) {
			lazy[ind] += val;
			propagate(ind,low,high);
			return ;
		}
		// last case has to be no overlap case
		int mid = (low + high) >> 1; 
		update(2*ind+1, low, mid, l, r, val);
		update(2*ind+2, mid+1, high, l, r, val); 
		seg[ind] = min(seg[2*ind+1], seg[2*ind+2]); 
	}

	ll query(int ind, int low, int high, int l, int r) {
 
		// update if any updates are remaining 
		// as the node will stay fresh and updated 
		propagate(ind,low,high);
 
		// no overlap return 0; 
		if(high < l or r < low) {
			return INT64_MAX; 
		}
 
		// complete overlap 
		if(low>=l && high <= r) return seg[ind]; 
 
		int mid = (low + high) >> 1; 
		ll left = query(2*ind+1, low, mid, l, r);
		ll right = query(2*ind+2, mid+1, high, l, r);
		return min(left,right); 
	}
};


int main(){
	fast();

	int n,q;
	cin>>n>>q;

	vector<ll>v(n);
	for(int i=0;i<n;i++) cin>>v[i];

	SegmentTree s(v);

	while(q--){
		int type;
		cin>>type;

		if(type==1){
			int a,b;
			cin>>a>>b;

			cout<<s.query(0,0,n-1,a,b)<<endl;
		}else{
			int a,b,c;
			cin>>a>>b>>c;

			s.rangeIncrease(0,0,n-1,a,b,c);
		}
	}

	return 0;
}