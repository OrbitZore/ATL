template<class T>
struct interval{
	static constexpr size_t dim{1};
	T a[2];
	T size()const{T x=a[1]-a[0]+1;return x<0?0:x;}
	T& operator[](size_t i){return a[i];}
	const T& operator[](size_t i)const {return a[i];}
	array<interval<T>,2> split()const{
		T mid=(a[0]+a[1])/2;
		return {a[0],mid,mid+1,a[1]};
	}
	bool in(const interval &b)const{return b.a[0]<=a[0]&&a[1]<=b.a[1];}
	bool cross(const interval &b)const{return min(a[1],b.a[1])>=max(a[0],b.a[0]);}
};
template<class T,size_t d>
struct kinterval{
	static constexpr size_t dim{d};
	interval<T> a[d];
	interval<T>& operator[](size_t i){return a[i];}
	const interval<T>& operator[](size_t i)const {return a[i];}
	T size()const{
		T x=a[0].size();
		for (size_t i=1;i<d;i++) x*=a[i].size();
		return x;
	}
	array<kinterval<T,d>,1<<d> split()const{
		array<kinterval<T,d>,1<<d> t;
		for (size_t i=0;i<d;i++){
			auto mi=a[i].split();
			for (size_t k=0;k<(1<<d);k++) t[k][i]=mi[(bool)(k&(1<<i))];
		}
		return t;
	}
	bool in(const kinterval &b)const{for (size_t i=0;i<d;i++) if (!a[i].in(b.a[i])) return false;return true;}
	bool cross(const kinterval &b)const{for (size_t i=0;i<d;i++) if (!a[i].cross(b.a[i])) return false;return true;}
};
template<class T,class invalT>
struct segtree:public invalT{
	using intervalT=invalT;
	using invalT::dim;
	segtree(const invalT &lr):invalT(lr){}
	segtree(invalT&& lr):invalT(lr){}
	T fadd{0},fmul{1},fsum{0};
	vector<segtree> ch;
	void wake(){
		if (ch.empty()){
			ch.reserve(1<<dim);
			for (auto &i:invalT::split())
				if (i.size()>=1)
					ch.emplace_back(segtree(move(i)));
		}
	}
	void dmul(const T& v){
		fmul*=v;
		fadd*=v;
		fsum*=v;
	}
	void dadd(const T& v){
		fadd+=v;
		fsum+=v*this->size();
	}
	void download(){
		if (fmul!=1){
			for (auto &i:ch) i.dmul(fmul);
			fmul=1;
		}
		if (fadd!=0){
			for (auto& i:ch) i.dadd(fadd);
			fadd=0;
		}
	}
	void upload(){
		fsum=0;
		for (auto& i:ch) fsum+=i.fsum;
	}
};
template<class T0,class T1,class T2>
void edit(T0& tree,const typename T0::intervalT& inval,void (T0::*const dfunc)(T1),const T2& v){
	if (tree.in(inval)) return (tree.*dfunc)(v);
	tree.wake();
	tree.download();
	for (auto& i:tree.ch) if (i.cross(inval)) edit(i,inval,dfunc,v);
	tree.upload();
}
template<class T0,class T1,class T2,class opT>
T2 query(T0& tree,const typename T0::intervalT& inval,T1 T0::*const dfunc,const T2& ini,const opT& op){
	if (tree.in(inval)) return op(ini,tree.*dfunc);
	tree.wake();
	tree.download();
	T2 a=ini;
	for (auto& i:tree.ch) if (i.cross(inval)) a=op(a,query(i,inval,dfunc,ini,op));
	return a;
}