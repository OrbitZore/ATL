template <class vT>
struct fedge{int u,v;vT cap,flow;fedge* iedge;};
template <class vT>
struct cfedge{int u,v;vT cap,cost,flow;cfedge* iedge;};
template <class edgeT>
struct network:public vector<list<edgeT>>{
	using vector<list<edgeT>>::vector;
	using eT=edgeT;
	using esT=list<eT>;
	using GT=vector<esT>;
	eT* addFlow(const eT &a){
		auto &l=GT::operator[](a.u);
		return &*l.insert(l.end(),a);
	}
	void add2Flow(eT a){
		a.flow=0;
		auto b=addEdge(a);
		swap(a.u,a.v);a.cap=0;
		auto c=addEdge(a);
		tie(b->iedge,c->iedge)=make_tuple(c,b);
	}
};