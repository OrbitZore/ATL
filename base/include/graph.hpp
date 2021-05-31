template <class vT>
struct wedge{int u,v;vT w;};
template <class vT>
struct sedge{int u,v;const constexpr static vT w=1;};
template <template <class vT> class etT,class vT>
struct graph:public vector<vector<etT<vT>>>{
	using eT=etT<vT>;
	using esT=vector<eT>;
	using GT=vector<esT>;
	using vector<vector<etT<vT>>>::vector;
	void addEdge(const eT &a){GT::operator[](a.u).push_back(a);}
	void add2Edge(eT a){addEdge(a);swap(a.u,a.v);addEdge(a);}
};