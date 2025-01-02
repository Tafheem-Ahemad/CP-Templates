#include<bits/stdc++.h>

// binary_lifting(root,-1);

int up[200500][22];
int level[200500];
void binary_lifting(int node,int par,int lev=1){

	up[node][0]=par;
	level[node]=lev;

	for(int i=1;i<22;i++){
		if(up[node][i-1] != -1){
			int x=up[node][i-1];
			up[node][i]=up[x][i-1];
		}else{
			up[node][i]=-1;
		}
	}

	for(auto i:g[node]){
		if(i==par) continue;
		binary_lifting(i,node,lev+1);
	}
}

int kthAncester(int a,int k){
	for(int i=20;i>=0;i--){
		if(a==-1) break;
		if((k>>i & 1) == 1){
			a=up[a][i];
		}
	}

	return a;
}

int LCA(int a,int b){
	if(level[a] > level[b]){
		swap(a,b);
	}

	ll z=level[b]-level[a];

	b=kthAncester(b,z);

	if(b==a) return a;

	for(int i=20;i>=0;i--){
		if(up[a][i] != up[b][i]){
			a=up[a][i];
			b=up[b][i];
		}
	}

	return kthAncester(a,1);
}
