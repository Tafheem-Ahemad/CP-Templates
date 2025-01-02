
// Implementation

class DSU{
	public: 
	vector<int>parent;
	vector<int>size;
	int V;
	int connected_component;

	DSU(int n){
		V=n;
		connected_component=n;
		parent.resize(V+5,0);
		size.resize(V+5,1);
		for(int i=0;i<parent.size();i++){
			parent[i]=i;
		}
	}

	int find(int a){
		if(parent[a]==a) return a;
		return parent[a]=find(parent[a]);
	}

	void Union (int a,int b){
		a=find(a);
		b=find(b);
		if(a==b) return ;

		connected_component--;

		if(size[a]< size[b]){
			size[b]+=size[a];
			parent[a]=b;
		}else{
			size[a]+=size[b];
			parent[b]=a;
		}
	}
};