template<class Tx,class Ty=Tx>
//	class cmp=less<decltype(declval<Tx>()+declval<Ty>())>>
struct slope_optimizer{
	using Txy=decltype(declval<Tx>()+declval<Ty>());
	using iter=typename map<Tx,Ty>::iterator;
	using v2=vec2<Txy>;
	template<class T1,class T2>
	static v2 _v(const pair<T1,T2>& p){return {p.first,p.second};}
	static v2 _v(const Tx& x,const Ty& y){return {x,y};}
	static v2 _v(const v2& x){return x;}
	static v2 _v(const iter& i){return _v(*i);}
	template<class fT>
	struct base_slopcmp{
		template<class T>
		bool operator()(const vec2<T>& a,const vec2<T>& b)const{
			return crs(a,b)>0;
		}
		template<class T1,class T2,class T3>
		Txy operator()(const T1& a,const T2& b,const T3& c)const{
			const auto& aa=fT::_v(a),bb=fT::_v(b),cc=fT::_v(c);
			return crs(bb-aa,cc-bb);
		}
	};
	using slopcmp=base_slopcmp<slope_optimizer>;
	map<v2,iter,slopcmp> ks;
	map<Tx,Ty> points;
	void _eraseik(const iter& j){ks.erase(_v(j)-_v(prev(j)));}
	void _eraseik(const iter& i,const iter& j){ ks.erase(_v(*j)-_v(*i));}
	void _insertik(const iter& i,const iter& j){ks[_v(*j)-_v(*i)]=j;}
	void check(){
		if (points.size()>=3){
			auto i=points.begin(),j=next(i),k=next(j);
			auto kj=ks.begin(),kk=next(kj);
			while (k!=points.end()){
				assert(slopcmp()(i,j,k));
				assert((kj!=ks.end()&&kk!=ks.end()));
				assert(kj->first==_v(j)-_v(i));
				assert(kk->first==_v(k)-_v(j));
				tie(i,j,k)=make_tuple(j,k,next(k));
				tie(kj,kk)=make_tuple(kk,next(kk));
			}
		}
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
//		check();
		return 1;
	}
	pair<Tx,Ty> getK(Txy k){
		auto ki=ks.upper_bound(vec2<Txy>{1,k});
		if (ki==ks.end()) {
			return *--points.end();
		}
		return *prev(ki->second);
	}
};