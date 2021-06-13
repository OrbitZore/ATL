#define op_mint(op)\
_mint operator op (const _mint a)const{_mint k(*this);k op##=a;return k;}
#define cmp_mint(op)\
bool operator op (const _mint a)const{return v op a.v;}
template<class T>
struct _mint{
	T v;
	static T mod;
	_mint()=default;
	_mint(const T &a){(v=a%mod)<0&&(v+=mod);}
	_mint& operator+=(const _mint a){return (v+=a.v)>=mod&&(v-=mod),*this;}
	_mint& operator-=(const _mint a){return (v-=a.v)<0&&(v+=mod),*this;}
	_mint& operator*=(const _mint a){return (v*=a.v)%=mod,*this;}
	op_mint(+) op_mint(-) op_mint(*)
	cmp_mint(<) cmp_mint(>) cmp_mint(<=) cmp_mint(>=) cmp_mint(!=) cmp_mint(==)
	#ifdef ATL_MATH
	_mint inverse(){_mint a;a.v=get<1>(Fexgcd(v,mod));return a;}
	_mint& operator/=(const _mint a){return (*this)*=a.inverse()%=mod,*this;}
	op_mint(/)
	#endif
};
template<class T>
T _mint<T>::mod;
template<class T>
ostream& operator<<(ostream& os,const _mint<T>& a){return os<<a.v;}
template<class T>
istream& operator>>(istream& os,_mint<T>& a){T k;os>>k;a=_mint<T>(k);return os;}
using mint=_mint<int>;
using mll=_mint<ll>;