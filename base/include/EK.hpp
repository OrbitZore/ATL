template<class vT,class GT>
vT EK(GT &G,int source,int sink){
	vector<typename GT::value_type::value_type*> path(G.size());	
	vT totflow=0;
	while (true){
		vector<vT> flow(G.size());
		queue<int> q;
		flow[source]=INF;
		q.push(source);
		while (q.size()){
			int x=q.front();q.pop();
			for (auto &e:G[x])
				if (!flow[e.v]&&e.cap>e.flow){
					path[e.v]=&e;
					flow[e.v]=min(flow[e.u],e.cap-e.flow);
					q.push(e.v);
				}
			if (flow[sink]) break;
		}
		if (!flow[sink]) break;
		for (auto i=path[sink];i!=path[source];i=path[i->u]){
			i->flow+=flow[sink];
			i->iedge->flow-=flow[sink];
		}
		totflow+=flow[sink];
	}
	return totflow;
}