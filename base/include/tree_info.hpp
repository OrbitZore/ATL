
template<class T>
struct tree_info{
	T& G;
	vec<int> sz,deep,fat;
	vec<int> dfn,invdfn,top;
	int dfni=0;
	tree_info(T &G,int u):G(G){
		sz.resize(G.size());
		deep.resize(G.size());
		fat.resize(G.size());
		dfn.resize(G.size());
		invdfn.resize(G.size());
		top.resize(G.size());
		dfs1(u);dfs2(u);
	}
	void dfs1(int u,int fa=-1){
		sz[u]++;
		fat[u]=fa==-1?u:fa;
		deep[u]=fa==-1?0:deep[fa]+1;
		for (auto [u,v]:G[u])
			if (v!=fa){
				dfs1(v,u);
				sz[u]+=sz[v];
			}
		if (G[u].size())
			iter_swap(max_element(all(G[u]),[&](auto a,auto b){return sz[a.v]<sz[b.v];}),G[u].begin());
	}
	void dfs2(int u,int fa=-1,bool f=false){
		invdfn[dfn[u]=dfni++]=u;
		top[u]=f?top[fa]:u;
		bool nopt=true;
		for (auto [u,v]:G[u]) if (v!=fa)
			dfs2(v,u,exchange(nopt,false));
	}
};
template<class T,class iniT,class funcT>
iniT tree_query(tree_info<T>& t,int x,int y,iniT val,funcT func){
    while(t.top[x]!=t.top[y]){
        if(t.deep[t.top[x]]<t.deep[t.top[y]]) swap(x,y);
        func(val,t.dfn[t.top[x]],t.dfn[x]);
        x=t.fat[t.top[x]];
    }
	if (t.dfn[x]>t.dfn[y]) swap(x,y);
    func(val,t.dfn[x],t.dfn[y]);
    return val;
}
template<class T,class funcT>
void tree_edit(tree_info<T>& t,int x,int y,funcT func){
    while(t.top[x]!=t.top[y]){
        if(t.deep[t.top[x]]<t.deep[t.top[y]]) swap(x,y);
        func(t.dfn[t.top[x]],t.dfn[x]);
        x=t.fat[t.top[x]];
    }
	if (t.dfn[x]>t.dfn[y]) swap(x,y);
    func(t.dfn[x],t.dfn[y]);
}
template<class T>
int tree_lca(tree_info<T>& t,int x,int y){
    while(t.top[x]!=t.top[y]){
        if(t.deep[t.top[x]]<t.deep[t.top[y]]) swap(x,y);
        x=t.fat[t.top[x]];
    }
	if (t.dfn[x]>t.dfn[y]) swap(x,y);
	return x;
}