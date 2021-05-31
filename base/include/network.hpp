template <class vT>
struct fedge{int u,v;vT cap,flow;fedge* iedge;};
template <class vT>
struct network:public vector<list<fedge<vT>>>{
	using vector<list<fedge<vT>>>::vector;
	using eT=fedge<vT>;
	using esT=list<eT>;
	using GT=vector<esT>;
	eT* addEdge(const eT &a){
		auto &l=GT::operator[](a.u);
		return &*l.insert(l.end(),a);
	}
	void add2Edge(eT a){addEdge(a);swap(a.u,a.v);addEdge(a);}
	void add2Flow(const eT &a){
		auto b=addEdge({a.u,a.v,a.cap,0}),
			 c=addEdge({a.v,a.u,0,0});
		tie(b->iedge,c->iedge)=make_tuple(c,b);
	}
};