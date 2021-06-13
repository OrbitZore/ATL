template<class T>
struct segtree{
    T fsum;
    virtual ~segtree(){}
    virtual void dadd(const T &nadd)=0;
    virtual void add(const ll &l,const ll &r,const T &nadd)=0;
    virtual void dmul(const T &nadd)=0;
    virtual void mul(const ll &l,const ll &r,const T &nadd)=0;
    virtual T sum(const ll &l,const ll &r)=0;
};
template<class T,class U>
unique_ptr<segtree<T>> make_seg(const U& op,const U& ed);
template<class T>
struct segtreec:public segtree<T>{
	using segtree<T>::fsum;
    unique_ptr<segtree<T>> lson,rson;
    ll count,mid;
    T fadd,fmul;
    template<class U>
    segtreec(const U& op,const U& ed):fadd(0),fmul(1){
    	mid=(count=ed-op)>>1;
    	lson=make_seg<T>(op,op+mid);
    	rson=make_seg<T>(op+mid,ed);
    	pushup();
    }
    void pushdown(){
        lson->dmul(fmul);
        rson->dmul(fmul);
        fmul=1;
        lson->dadd(fadd);
        rson->dadd(fadd);
        fadd=0;
    }
    void pushup(){
        fsum=lson->fsum+rson->fsum;
    }
    void dadd(const T &nadd){
        fadd+=nadd;
        fsum+=nadd*count;
    }
    void add(const ll &l,const ll &r,const T &nadd){
        if (l<=1&&count<=r)
            dadd(nadd);
        else{
            pushdown();
            if (l<=mid) lson->add(l,r,nadd);
            if (r>mid) rson->add(l-mid,r-mid,nadd);
            pushup();
        }
    }
    void dmul(const T &nmul){
    	fmul*=nmul;
        fadd*=nmul;
        fsum*=nmul;
    }
    void mul(const ll &l,const ll &r,const T &nmul){
        if (l<=1&&count<=r)
            dmul(nmul);
        else{
            pushdown();
            if (l<=mid) lson->mul(l,r,nmul);
            if (r>mid) rson->mul(l-mid,r-mid,nmul);
            pushup();
        }
    }
    T sum(const ll &l,const ll &r){
        if (l<=1&&count<=r) return fsum;
        pushdown();
        T ans=0;
        if (l<=mid) ans+=lson->sum(l,r);
        if (r>mid) ans+=rson->sum(l-mid,r-mid);
        return ans;
    }
};
template<class T>
struct segtreen:public segtree<T>{
	using segtree<T>::fsum;
	template<class U>
    segtreen(const U& op,const U& ed){fsum=*op;}
    void dadd(const T &nadd){fsum+=nadd;}
    void add(const ll &l,const ll &r,const T &nadd){fsum+=nadd;}
    void dmul(const T &nmul){fsum*=nmul;}
    void mul(const ll &l,const ll &r,const T &nmul){fsum*=nmul;}
    T sum(const ll &l,const ll &r){return fsum;}
};
template<class T,class U>
unique_ptr<segtree<T>> make_seg(const U& op,const U& ed){
	if (ed-op==1) return unique_ptr<segtree<T>>(new segtreen<T>(op,ed));
	else return unique_ptr<segtree<T>>(new segtreec<T>(op,ed));
}