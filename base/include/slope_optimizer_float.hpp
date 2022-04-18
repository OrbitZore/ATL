template<class Tx,class Ty=Tx,class Tk=double>
//	class cmp=less<decltype(declval<Tx>()+declval<Ty>())>>
struct slope_optimizer_float{
	using Txy=decltype(declval<Tx>()+declval<Ty>());
	using iter=typename map<Tx,Ty>::iterator;
	using v2=pair<Tx,Ty>;
	static v2 _v(const Tx& x,const Ty& y){
		return {x,y};
	}
	static v2 _v(const v2& x){
		return x;
	}
	static v2 _v(const iter& i){
		return _v(*i);
	}
	static Tk _k(const v2& a,const v2& b){//a->b
		return (Tk)(b.second-a.second)/(b.first-a.first);
	}
	template<class fT>
	struct base_slopcmp{
		template<class T1,class T2,class T3>
		Tk operator()(const T1& a,
										const T2& b,
										const T3& c)const{
			const auto& aa=fT::_v(a);
			const auto& bb=fT::_v(b);
			const auto& cc=fT::_v(c);
			return fT::_k(bb,cc)-fT::_k(aa,bb);
		}
	};
	using slopcmp=base_slopcmp<slope_optimizer_float>;
	map<Tk,iter> ks;
	map<Tx,Ty> points;
	void _eraseik(const iter& j){
		ks.erase(_k(_v(prev(j)),_v(j)));
	}
	
	void _eraseik(const iter& i,const iter& j){
		ks.erase(_k(_v(*i),_v(*j)));
	}
	
	void _insertik(const iter& i,const iter& j){
		ks[_k(_v(*i),_v(*j))]=j;
	}
	int insert(Tx x,Ty y){
		if (points.size()==0) {points.insert({x,y});return 0;}
		auto v=_v(x,y);
		auto i1=points.lower_bound(x);
		if (i1!=points.end()&&i1->first==x){//same
			if (y>=i1->second) return -1;
			if (i1!=points.begin())
				_eraseik(i1);
			if (next(i1)!=points.end())
				_eraseik(i1,next(i1));
			i1->second=y;
		}else{
			if (points.size()>=2&&i1!=points.end()&&i1!=points.begin()){
                if (slopcmp()(prev(i1),v,i1)<=0) return -1;
                _eraseik(i1);
			}
			i1=points.insert({x,y}).first;
		}
		decltype(i1) i0;
		if (i1!=points.begin()){
			i0=prev(i1);
			if (i0!=points.begin()){
				auto i00=prev(i0);
				while (slopcmp()(i00,i0,i1)<=0){
					_eraseik(i00,i0);
					points.erase(i0);
					if (i00==points.begin()){
						i0=i00;
						break;
					}
					tie(i00,i0)=make_tuple(prev(i00),i00);
				}
			}
		}
		auto i2=next(i1);
		if (i2!=points.end()){
			auto i3=next(i2);
			while (i3!=points.end()&&slopcmp()(i1,i2,i3)<=0){
				_eraseik(i2,i3);
				points.erase(i2);
				tie(i2,i3)=make_tuple(i3,next(i3));
			}
			_insertik(i1,i2);
		}
		if (i1!=points.begin()) _insertik(i0,i1);
		return 1;
	}
	pair<Tx,Ty> getK(Tk k){
		auto ki=ks.upper_bound(k);
		if (ki==ks.end()) {
			return *--points.end();
		}
		return *prev(ki->second);
	}
};