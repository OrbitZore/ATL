template<class T>
struct segtree{
	const int l,r,mid;
	T fadd,fmul,fsum;
	unique_ptr<segtree> ch[2];
	segtree(const int l,const int r):l(l),r(r),mid((l+r)/2),
		fadd(0),fmul(1),fsum(0){
		if (l!=r){
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
	void down(){
		if (ch[0]){
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
	}
	void up_sum(){
		if (ch[0]){
			fsum=ch[0]->fsum+ch[1]->fsum;
		}
	}
	void add(const int L,const int R,const T& v){
		if (L<=l&&r<=R) return dadd(v);
		down();
		if (L<=mid) ch[0]->add(L,R,v);
		if (mid<R) ch[1]->add(L,R,v);
		up_sum();
	}
	void mul(const int L,const int R,const T& v){
		if (L<=l&&r<=R) return dmul(v);
		down();
		if (L<=mid) ch[0]->mul(L,R,v);
		if (mid<R) ch[1]->mul(L,R,v);
		up_sum();
	}
	
	T sum(const int L,const int R){
		if (L<=l&&r<=R) return fsum;
		T fsum=0;
		down();
		if (L<=mid) fsum+=ch[0]->sum(L,R);
		if (mid+1<=R) fsum+=ch[1]->sum(L,R);
		up_sum();
		return fsum;
	}
};