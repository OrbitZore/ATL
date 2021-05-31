template<class vT=int,class GT>
vector<vT> dijstra(const GT &G,int i){
	using P=pair<vT,int>;
	const auto n=G.size();
	vector<vT> dis(n,(vT)INF);
	vector<bool> book(n,true);
	dis[i]=0;
	set<P> p;
	p.insert(make_pair(0,i));
	int now=i;
	while (p.size()){
		now=p.begin()->second;p.erase(p.begin());
		if (!book[now]) continue;
		book[now]=false;
		for (auto &e:G[now])
			if (book[e.v]&&dis[e.v]>dis[now]+e.w){
				p.erase(make_pair(dis[e.v],e.v));
				dis[e.v]=dis[now]+e.w;
				p.insert(make_pair(dis[e.v],e.v));
			}
	}
	return dis;
}