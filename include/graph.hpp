template <class vT>
struct wedge{int u,v;vT w;};
template <class vT>
struct sedge{int u,v;const constexpr static vT w=1;};
template <class eT=sedge<int>>
struct graph:public vector<vector<eT<vT>>>{
	using esT=vector<eT>;
	using GT=vector<esT>;
	using GT::vector;
	void addEdge(const eT &a){GT::operator[](a.u).push_back(a);}
	void add2Edge(eT &&a){addEdge(a);swap(a.u,a.v);addEdge(a);}
};
