template<class vT,class T,class lT,class ITT>
pair<vT,vT> mcmf_dfs(T &G,int s,int t,lT &level,const ITT &dis,vT maxf=INF){
	if (s==t||maxf==0) return {maxf,0};
	vT flow=0,cost=0;
	for (auto &e:G[s]){
		int v=e.v;
		if (level[v]==level[s]+1&&dis[v]==dis[s]+e.cost&&e.flow<e.cap){
			vT f,c;
            tie(f,c)=mcmf_dfs(G,v,t,level,min(e.cap-e.flow,maxf));
			if (f>0){
				e.flow+=f;
				e.iedge->flow-=f;
				flow+=f;
				maxf-=f;
                cost+=c+f*e.cost;
				if (maxf==0) break;
			}
		}
	}
	if (flow==0) level[s]=0;
	return make_pair(flow,cost);
}

template<class vT,class T>
pair<vT,vT> mcmf(T &G,int s,int t){
    const size_t n=G.size();
	vT ans=0;
    vector<int> level;
    vector<vT> dis;
	while([&](){
        dis=vector<vT>(n,(vT)INF/2);
		level=vector<int>(n,0);
        queue<int> q;
        level[s]=1;dis[s]=0;
        q.push(s);
        while(!q.empty()){
            int x=q.front();q.pop();
            for(auto &e:G[x]){
                int v=e.v;
                if(!level[v])
                    if(e.flow<e.cap&&dis[v]>dis[s]+e.cost){
                        dis[v]=dis[s]+e.cost;
                        level[v]=level[x]+1;
                        q.push(v);
                    }
            }
        }
        return level[t];
    }()){
		while(vT tmp=mcmf_dfs<vT>(G,s,t,level)) ans+=tmp;
	}
	return ans;
}