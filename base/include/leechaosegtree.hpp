
struct Line{
	vec2<double> a,b;
	Line():a({0,0}),b({0,0}){}
	Line(vec2<double> _a,vec2<double> _b):a(min(_a,_b)),b(max(_a,_b)){}
	double at(double x)const{
		if (a==vec2<double>{0,0}&&b==vec2<double>{0,0}) return MINF;
		if (x==b[0]) return b[1];
		if (x==a[0]) return a[1];
		vec2<double> v=b-a;
		if (v[0]==0) return x==a[0]?b[1]:(double)MINF;
		v=v/v[0]*(x-a[0]);
		return (v+a)[1];
	}
	bool fullcover(const Line& line,double l,double r)const{
		return at(l)>=line.at(l)&&at(r)>=line.at(r);
	}
};

struct segtree{
	const int l,r;int mid{INF};
	Line line;int linei{0};
	segtree* ch[2];
	segtree(const int l,const int r):l(l),r(r){}
	bool unwake(){return mid==(int)INF;}
	bool wake(){
		if (unwake()){
			mid=(l+r)/2;
			ch[0]=(mnew<segtree>(l,mid));
			ch[1]=(mnew<segtree>(mid+1,r));
			return true;
		}
		return false;
	}
	
	pair<double,int> get(double p)const{
		return {line.at(p),linei};
	}
	
	pair<double,int> merge(pair<double,int> a,double p)const{return max(a,get(p));}
};

void addLine(segtree& tree,const int& L,const int& R,const Line& line,const int& i){
	const auto& l=tree.l,&r=tree.r,&m=tree.mid;
	if (L<=l&&r<=R){
		if (tree.line.fullcover(line,l,r))
			return void();
		if (line.fullcover(tree.line,l,r))
			return tie(tree.line,tree.linei)=tie(line,i),void();
	}
	tree.wake();
	if (!(R<l||m<L)&&(L==R||!tree.line.fullcover(line,l,m)))
		addLine(*tree.ch[0],L,R,line,i);
	if (!(R<m+1||r<L)&&(L==R||!tree.line.fullcover(line,m,r+1)))
		addLine(*tree.ch[1],L,R,line,i);
}

pair<double,int> getDaze(segtree& tree,const int& LR){
	if (LR==tree.l&&tree.r==LR || tree.unwake())
		return tree.get(LR);
	if (LR<=tree.mid) return tree.merge(getDaze(*tree.ch[0],LR),LR);
	else return tree.merge(getDaze(*tree.ch[1],LR),LR);
}