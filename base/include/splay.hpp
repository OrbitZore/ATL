template<class T,class iT>
struct splay{
	struct Tnode{
	    T val;
		iT cnt,size;
	    Tnode *ch[2];
	    Tnode (T v,iT c){val=v;size=cnt=c;}
	    void maintain(){
	    	size=ch[0]->size+ch[1]->size+cnt;
	    }
	    char cmp(const T& v){
	        if (v==val) return -1;
	        return val<v;
	    }
	    char cmpkth(iT &k){
	        iT p=k-ch[0]->size;
	        if (p<=0) return 0;
	        k=p;p-=cnt;
	        if (p<=0) return -1;
	        k=p;return 1;
	    }
	};
	static Tnode nilnode;
	static Tnode* nil;
    Tnode *head;
    
    splay(){
        head=nil;
    }
    
	void rotate(Tnode *&e,const char d){
		if (e==nil) return ;
		Tnode *&a=e,*&b=e->ch[d],*&c=e->ch[d]->ch[d^1];
		swap(a,b);swap(b,c);
		e->ch[d^1]->maintain();
		e->maintain();
	}
	
    void Splay(Tnode *&e,const T& v){
    	if (e==nil) return ;
    	char d1=e->cmp(v);
    	if (d1==-1 || e->ch[d1]==nil){
    		return ;
    	}else{
    		Tnode *&n1=e->ch[d1];
    		char d2=n1->cmp(v);
    		if (d2==-1 || n1->ch[d2]==nil) {rotate(e,d1);return ;}
    		else{
    			Splay(n1->ch[d2],v);
    			if (d1==d2) {rotate(e,d1);rotate(e,d1);}
    			else {rotate(n1,d2);rotate(e,d1);}
    		}
    	}
    }
    
    void splaykth(Tnode *&e,iT& k){
    	if (e==nil) return ;
    	char d1=e->cmpkth(k);
    	if (d1==-1 || e->ch[d1]==nil){
    		return ;
    	}else{
    		Tnode *&n1=e->ch[d1];
    		char d2=n1->cmpkth(k);
    		if (d2==-1 || n1->ch[d2]==nil) {rotate(e,d1);return ;}
    		else{
    			splaykth(n1->ch[d2],k);
    			if (d1==d2) {rotate(e,d1);rotate(e,d1);}
    			else {rotate(n1,d2);rotate(e,d1);}
    		}
    	}
    }
    
    void _insert(const T& vs,const iT& ss,Tnode *&e){
    	if (e==nil){
    		e=new Tnode(vs,ss);
    		e->ch[0]=e->ch[1]=nil;
    		return ;
    	}
    	char d=e->cmp(vs);
    	if (d==-1){
    		e->cnt+=ss;
    	}else _insert(vs,ss,e->ch[d]);
    }
    
    void insert(const T& vs,const iT& ss=1){
    	_insert(vs,ss,head);
    	Splay(head,vs);
    }
    
    void erase(const T& vs,const iT& ss=1){
    	Splay(head,vs);
    	if (ss<head->cnt){
    		head->cnt-=ss;
    		head->size-=ss;
    		return ;
    	}
    	Tnode *l=head->ch[0],*r=head->ch[1];
    	delete head;
    	if (r!=nil){
    		Splay(r,vs+1);
    		r->ch[0]=l;
    		r->maintain();
    		head=r;
    	}else head=l;
    }
    
    iT rank(T v){
    	Splay(head,v);
        return head->ch[0]->size+(head->val<v?head->cnt:0)+1;
    }
	
    Tnode* kth(iT k){
    	splaykth(head,k);
        return head;
    }
    
};
template<class T,class IT>
typename splay<T,IT>::Tnode splay<T,IT>::nilnode(0,0);
template<class T,class IT>
typename splay<T,IT>::Tnode* splay<T,IT>::nil=&splay<T,IT>::nilnode;