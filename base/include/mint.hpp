#ifndef __OP__
#define __OP__
#define def_op(op)\
this_type operator op (const this_type& a)const{this_type k(*this);k op##=a;return k;}
#define def_cmp(op,n2)\
bool operator op (const this_type& a)const{return n2 op a.n2;}
#define def_all_cmp(n2)\
def_cmp(<,n2) def_cmp(>,n2) def_cmp(<=,n2) \
def_cmp(>=,n2) def_cmp(!=,n2) def_cmp(==,n2)
#endif
template<class T,class uT,ll mod>
struct _mint{
	using this_type=_mint;
	T v;
	_mint()=default;
	template<class iT>
	_mint(const iT& a){v=a%mod;v+=v<0?mod:0;}
	_mint& operator+=(const _mint& a){return (v+=a.v)>=mod&&(v-=mod),*this;}
	_mint& operator-=(const _mint& a){return (v-=a.v)<0&&(v+=mod),*this;}
	_mint& operator*=(const _mint& a){return (v=((uT)v*a.v)%mod),*this;}
	def_op(+) def_op(-) def_op(*)
	def_all_cmp(v)
	#ifdef ATL_MATH
	_mint inverse()const{return power(*this,mod-2);}
	_mint& operator/=(const _mint& a){return (*this)*=a.inverse(),*this;}
	def_op(/)
	#endif
};
template<class T,class uT,ll mod>
ostream& operator<<(ostream& os,const _mint<T,uT,mod>& a){return os<<a.v;}
template<class T,class uT,ll mod>
istream& operator>>(istream& os,_mint<T,uT,mod>& a){T k;os>>k;a=_mint<T,uT,mod>(k);return os;}
using mint=_mint<int,long long,998244353>;
using mll=_mint<long long,__int128,998244353>;