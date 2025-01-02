
// Implemaintation

vector<int> topo_sort(int k,vector<vector<int>>&edges){
    list<int> g[k+5];
    vector<int>indegree(k+2,0);
    for(auto &it:edges){
        g[it[0]].push_back(it[1]);

        indegree[it[1]]++;
    }

    queue<int>q;
    for(int i=1;i<=k;i++){
        if(indegree[i]==0) q.push(i);
    }


    vector<int>ans;
    while(q.size()){
        int cur=q.front();
        q.pop();

        ans.push_back(cur);

        for(auto &it:g[cur]){
            indegree[it]--;
            if(indegree[it]==0){
                q.push(it);
            }
        }
    }

    return ans;
}