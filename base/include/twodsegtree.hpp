//Make sure every number in lr is pow of 2
//size of lr[0] and lr[1] are equal
template<class T,class IT=int>
struct segtree2d{
	const array<array<IT,2>,2> lr;
	IT mid[2]={0,0};
	T fadd={0},fmul={1},fsum={0};
	unique_ptr<segtree2d> ch[4];
	segtree2d(array<array<IT,2>,2> lr):lr(lr){}
	void wake(){
		if (mid[0]==0){
			mid[0]=(lr[0][0]+lr[0][1])>>1;
			mid[1]=(lr[1][0]+lr[1][1])>>1;
			ch[0].reset(new segtree2d({lr[0][0],mid[0],lr[1][0],mid[1]}));
			ch[1].reset(new segtree2d({lr[0][0],mid[0],mid[1]+1,lr[1][1]}));
			ch[2].reset(new segtree2d({mid[0]+1,lr[0][1],lr[1][0],mid[1]}));
			ch[3].reset(new segtree2d({mid[0]+1,lr[0][1],mid[1]+1,lr[1][1]}));
		}
	}
	void dmul(const T& v){
		fmul*=v;
		fadd*=v;
		fsum*=v;
	}
	void dadd(const T& v){
		fadd+=v;
		fsum+=v*(lr[0][1]-lr[0][0]+1)*(lr[1][1]-lr[1][0]+1);
	}
	void download(){
		if (fmul!=1){
			for (auto& i:ch) i->dmul(fmul);
			fmul=1;
		}
		if (fadd!=0){
			for (auto& i:ch) i->dadd(fadd);
			fadd=0;
		}
	}
	void upload(){
		fsum=ch[0]->fsum+ch[1]->fsum+ch[2]->fsum+ch[3]->fsum;
	}
};
template<class T0,class T1,class T2,class T3=decltype(declval<T0>().l)>
void edit(T0& tree,const T3& L0,const T3& R0,const T3& L1,const T3& R1,void (T0::*const& dfunc)(T1),const T2& v){
	if (L0<=tree.lr[0][0]&&tree.lr[0][1]<=R0&&
		L1<=tree.lr[1][0]&&tree.lr[1][1]<=R1) return (tree.*dfunc)(v);
	tree.wake();
	tree.download();
	if (L0<=tree.mid[0]){
		if (L1<=tree.mid[1]) edit(*tree.ch[0],L0,R0,L1,R1,dfunc,v);
		if (tree.mid[1]+1<=R1) edit(*tree.ch[1],L0,R0,L1,R1,dfunc,v);
	}
	if (tree.mid[0]+1<=R0){
		if (L1<=tree.mid[1]) edit(*tree.ch[2],L0,R0,L1,R1,dfunc,v);
		if (tree.mid[1]+1<=R1) edit(*tree.ch[3],L0,R0,L1,R1,dfunc,v);
	}
	tree.upload();
}
template<class T0,class T1,class T2,class opT,class T3=decltype(declval<T0>().l)>
T2 query(T0& tree,const T3& L0,const T3& R0,const T3& L1,const T3& R1,T1 T0::*const& dfunc,const T2& ini,const opT& op){
	if (L0<=tree.lr[0][0]&&tree.lr[0][1]<=R0&&
		L1<=tree.lr[1][0]&&tree.lr[1][1]<=R1) return op(ini,tree.*dfunc);
	tree.wake();
	tree.download();
	T2 a=ini;
	if (L0<=tree.mid[0]){
		if (L1<=tree.mid[1]) a=op(a,query(*tree.ch[0],L0,R0,L1,R1,dfunc,ini,op));
		if (tree.mid[1]+1<=R1) a=op(a,query(*tree.ch[1],L0,R0,L1,R1,dfunc,ini,op));
	}
	if (tree.mid[0]+1<=R0){
		if (L1<=tree.mid[1]) a=op(a,query(*tree.ch[2],L0,R0,L1,R1,dfunc,ini,op));
		if (tree.mid[1]+1<=R1) a=op(a,query(*tree.ch[3],L0,R0,L1,R1,dfunc,ini,op));
	}
	return a;
}
#define edit(t,l0,r0,l1,r1,dfunc,v) edit(t,l0,r0,l1,r1,&decltype(t)::dfunc,v)
#define query(t,l0,r0,l1,r1,fobj,v,op) query(t,l0,r0,l1,r1,&decltype(t)::fobj,v,op)