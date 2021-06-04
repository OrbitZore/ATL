template<class vT,class T,class lT>
vT dinic_dfs(T &G,int s,int t,lT &level,vT maxf=INF){
	if (s==t||maxf==0) return maxf;
	vT flow=0;
	for (auto &e:G[s]){
		int v=e.v;
		if (level[v]==level[s]+1&&e.flow<e.cap){
			vT f=dinic_dfs(G,v,t,level,min(e.cap-e.flow,maxf));
			if (f>0){
				e.flow+=f;
				e.iedge->flow-=f;
				flow+=f;
				maxf-=f;
				if (maxf==0) break;
			}
		}
	}
	if (flow==0) level[s]=0;
	return flow;
}

template<class vT,class T>
vT dinic(T &G,int s,int t){
    const size_t n=G.size();
	vT ans=0;
    vector<int> level;
	while([&](){
		level=vector<int>(n,0);
        queue<int> q;
        level[s]=1;
        q.push(s);
        while(!q.empty()){
            int x=q.front();q.pop();
            for(auto &e:G[x]){
                int v=e.v;
                if(!level[v])
                    if(e.flow<e.cap){
                        level[v]=level[x]+1;
                        q.push(v);
                    }
            }
        }
        return level[t];
    }()){
    	cerr<<1;
		while(vT tmp=dinic_dfs<vT>(G,s,t,level)) ans+=tmp;
	}
	return ans;
}