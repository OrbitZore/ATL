#define op_mint(op)\
_mint operator op (const _mint a)const{_mint k(*this);k op##=a;return k;}
#define cmp_mint(op)\
bool operator op (const _mint a)const{return v op a.v;}
template<class T,class uT>
struct _mint{
	T v;
	static T mod;
	_mint()=default;
	template<class iT>
	_mint(const iT &a){v=a%mod;v+=v<0?mod:0;}
	_mint& operator+=(const _mint a){return (v+=a.v)>=mod&&(v-=mod),*this;}
	_mint& operator-=(const _mint a){return (v-=a.v)<0&&(v+=mod),*this;}
	_mint& operator*=(const _mint a){return (v=((uT)v*a.v)%mod),*this;}
	op_mint(+) op_mint(-) op_mint(*)
	cmp_mint(<) cmp_mint(>) cmp_mint(<=) cmp_mint(>=) cmp_mint(!=) cmp_mint(==)
	#ifdef ATL_MATH
	_mint inverse()const{return get<1>(Fexgcd(v,mod));}
	_mint& operator/=(const _mint a){return (*this)*=a.inverse(),*this;}
	op_mint(/)
	#endif
};
template<class T,class uT>
T _mint<T,uT>::mod;
template<class T,class uT>
ostream& operator<<(ostream& os,const _mint<T,uT>& a){return os<<a.v;}
template<class T,class uT>
istream& operator>>(istream& os,_mint<T,uT>& a){T k;os>>k;a=_mint<T,uT>(k);return os;}
using mint=_mint<int,long long>;
using mll=_mint<long long,__int128>;