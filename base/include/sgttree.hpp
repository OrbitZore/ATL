template<class T,class iT>
struct sgttree{
	constexpr static double s_alpha=0.724;
	constexpr static double s_beta=0.35;
	struct Tnode{
        static Tnode nilnode;
        static Tnode* nil;
	    T val;
	    iT cnt,size,cover,rsize;
	    Tnode *ch[2];
	    Tnode (T v,iT c){val=v;cnt=size=c;rsize=(c!=0);cover=1;}
        ~Tnode(){
            if (ch[0]!=Tnode::nil) delete ch[0];
            if (ch[1]!=Tnode::nil) delete ch[1];
        }
	    void maintain(){
	                    size=cnt+ch[0]->size+ch[1]->size;
	                    rsize=(cnt!=0?1:0)+ch[0]->rsize+ch[1]->rsize;
	                    cover=1+ch[0]->cover+ch[1]->cover;}
	    void rmaintain(){maintain();cover=rsize;}
	    bool isBad(){return max(ch[0]->cover,ch[1]->cover)>=
	                        (s_alpha*cover);}
	    char cmp(T v){
	        if (v==val) return -1;
	        return v>=val;
	    }
	    char cmpkth(iT &k){
	        iT p=k-ch[0]->size;
	        if (p<=0) return 0;
	        k=p;p-=cnt;
	        if (p<=0) return -1;
	        k=p;return 1;
	    }
	};
    Tnode *head;
    
    sgttree():head(Tnode::nil){}
    ~sgttree(){if (head!=Tnode::nil) delete head;}
    int ci;
    void toArr(Tnode *e,vector<Tnode*> &g){
        if (e==Tnode::nil) return ;
        if (e->ch[0]!=Tnode::nil) toArr(e->ch[0],g);
        if (e->cnt) g.pb(e);
        if (e->ch[1]!=Tnode::nil) toArr(e->ch[1],g);
        if (!e->cnt) delete e;
    }

    Tnode* toTree(int l,int r,vector<Tnode*> &g){
        if (l>=r) return Tnode::nil;
        int mid=(l+r)>>1;
        Tnode &e=*(g[mid]);
        e.ch[0]=toTree(l,mid,g);
        e.ch[1]=toTree(mid+1,r,g);
        e.maintain();
        return &e;
    }

    void reBuild(Tnode *&e){
        if (e!=Tnode::nil){
        	vector<Tnode*> g;
        	g.reserve(e->cover);
            toArr(e,g);
            e=toTree(0,g.size(),g);
        }
    }

    Tnode **to;
    T v;iT s;
    void insert(Tnode *&e){
        if (e==Tnode::nil){
            e=new Tnode(v,s);
            e->ch[0]=e->ch[1]=Tnode::nil;
            return ;
        }
        char d=e->cmp(v);
        if (d==-1)
            e->cnt+=s;
        else insert(e->ch[d]);
        e->maintain();
        if (e->isBad()) to=&e,e->rmaintain();
    }

    void erase(Tnode *&e){
        if (e==Tnode::nil) return ;
        char d=e->cmp(v);
        if (d==-1)
            e->cnt=max(0,e->cnt-s);
        else erase(e->ch[d]);
        e->maintain();
    }

    void insert(T vs,iT ss=1){
        v=vs;s=ss;
        to=&Tnode::nil;
        insert(head);
        reBuild(*to);
    }

    void erase(T vs,iT ss=1){
        v=vs;s=ss;
        erase(head);
        if ((head->cover-head->rsize)>head->cover*s_beta)
        	reBuild(head);
    }

    iT rank(T v){
        Tnode *e=head;iT k=1;char d;
        while (e!=Tnode::nil&&(d=e->cmp(v))!=-1){
            if (d==1) k+=e->ch[0]->size+e->cnt;
            e=e->ch[d];
        }
        return k+e->ch[0]->size;
    }

    Tnode* kth(iT k){
        Tnode *e=head;char d;
        while ((d=e->cmpkth(k))!=-1) e=e->ch[d];
        return e;
    }
};
template<class T,class IT>
typename sgttree<T,IT>::Tnode sgttree<T,IT>::Tnode::nilnode=[](){
    Tnode nil(0,0);
    nil.rsize=nil.cover=0;
    nil.ch[0]=nil.ch[1]=&sgttree<T,IT>::Tnode::nilnode;;
    return nil;
}();
template<class T,class IT>
typename sgttree<T,IT>::Tnode* sgttree<T,IT>::Tnode::nil=&sgttree<T,IT>::Tnode::nilnode;