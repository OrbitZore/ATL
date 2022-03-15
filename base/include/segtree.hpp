
template<class T,class IT=int>
struct segtree{
	const IT l,r;IT mid;
	T fadd,fmul,fsum;
	unique_ptr<segtree> ch[2];
	segtree(const int l,const int r):l(l),r(r),mid(INF),fadd(0),fmul(1),fsum(0){}
	void wake(){
		if (mid==(IT)INF){
			mid=(l+r)/2;
			ch[0].reset(new segtree(l,mid));
			ch[1].reset(new segtree(mid+1,r));
		}
	}
	void dmul(const T& v){
		fmul*=v;
		fadd*=v;
		fsum*=v;
	}
	void dadd(const T& v){
		fadd+=v;
		fsum+=v*(r-l+1);
	}
	void download(){
		if (fmul!=1){
			ch[0]->dmul(fmul);
			ch[1]->dmul(fmul);
			fmul=1;
		}
		if (fadd!=0){
			ch[0]->dadd(fadd);
			ch[1]->dadd(fadd);
			fadd=0;
		}
	}
	void upload(){
		fsum=ch[0]->fsum+ch[1]->fsum;
	}
};
template<class T0,class T1,class T2,class T3=decltype(declval<T0>().l)>
void edit(T0& tree,const T3& L,const T3& R,void (T0::*const& dfunc)(T1),const T2& v){
	if (L<=tree.l&&tree.r<=R) return (tree.*dfunc)(v);
	tree.wake();
	tree.download();
	if (L<=tree.mid) edit(*tree.ch[0],L,R,dfunc,v);
	if (tree.mid+1<=R) edit(*tree.ch[1],L,R,dfunc,v);
	tree.upload();
}
template<class T0,class T1,class T2,class opT,class T3=decltype(declval<T0>().l)>
T2 query(T0& tree,const T3& L,const T3& R,T1 T0::*const& dfunc,const T2& ini,const opT& op){
	if (L<=tree.l&&tree.r<=R) return op(ini,tree.*dfunc);
	tree.wake();
	tree.download();
	T2 a=ini;
	if (L<=tree.mid) a=op(a,query(*tree.ch[0],L,R,dfunc,ini,op));
	if (tree.mid+1<=R) a=op(a,query(*tree.ch[1],L,R,dfunc,ini,op));
	return a;
}
#define edit(t,l,r,dfunc,v) edit(t,l,r,&decltype(t)::dfunc,v)
#define query(t,l,r,fobj,v,op) query(t,l,r,&decltype(t)::fobj,v,op)