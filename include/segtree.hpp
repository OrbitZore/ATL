template<class T,int count,class IT=ll>
struct SegTree{
    SegTree<T,count-1> ch[2];
    constexpr static IT mid=1ll<<(count-1);
    constexpr static IT tot=1ll<<count;
    T fadd,fsum;
    SegTree(){fadd=fsum=0;}
    void dadd(const T &nadd){
        fadd+=nadd;
        fsum+=nadd*tot;
    }
    void pushdown(){
        ch[0].dadd(fadd);
        ch[1].dadd(fadd);
        fadd=0;
    }
    void pushup(){
        fsum=ch[0].fsum+ch[1].fsum;
    }
    void add(const IT &l,const IT &r,const T &nadd){
        if (l<=1&&tot<=r)
            dadd(nadd);
        else{
            pushdown();
            if (l<=mid) ch[0].add(l,r,nadd);
            if (r>mid) ch[1].add(l-mid,r-mid,nadd);
            pushup();
        }
    }
    T sum(const IT &l,const IT &r){
        if (l<=1&&tot<=r) return fsum;
        pushdown();
        T ans=0;
        if (l<=mid) ans+=ch[0].sum(l,r);
        if (r>mid) ans+=ch[1].sum(l-mid,r-mid);
        return ans;
    }
};
template<class T,class IT>
struct SegTree<T,0,IT>{
    T fsum;
    SegTree(){fsum=0;}
    void dadd(const T &nadd){fsum+=nadd;}
    void add(const IT &l,const IT &r,const T &nadd){fsum+=nadd;}
    T sum(const IT &l,const IT &r){return fsum;}
};