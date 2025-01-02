

list<ll> g[200500];
 

void dfs_cycle(int u, int p, vl &color, vl &par, int& cyclenumber,vector<vector<ll>>&cycles)
{
 
    // already (completely) visited vertex.
    if (color[u] == 2) {
        return;
    }
 
    // seen vertex, but was not completely visited -> cycles detected.
    // backtrack based on parents to find the complete cycles.
    if (color[u] == 1) {
        vector<ll> v;
        cyclenumber++;
           
        int cur = p;
          v.push_back(cur);
 
        // backtrack the vertex which are
        // in the current cycles thats found
        while (cur != u) {
            cur = par[cur];
              v.push_back(cur);
        }
          cycles.push_back(v);
        return;
    }
    par[u] = p;
 
    // partially visited.
    color[u] = 1;
 
    // simple dfs on graph
    for (auto &v : g[u]) {
 
        // if it has not been visited previously
        if (v == par[u]) {
            continue;
        }
        dfs_cycle(v, u, color, par, cyclenumber , cycles);
    }
 
    // completely visited.
    color[u] = 2;
}
 

vector<vector<ll>> find_all_cycle(ll n,ll start){
	vl color(n+2,-1);
	vl par(n+2,-1);
	
	int cyclenumber = 0;
	vector<vector<ll>>cycles;
    dfs_cycle(start, -1, color, par, cyclenumber,cycles);

	return cycles;
}