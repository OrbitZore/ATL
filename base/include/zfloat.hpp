#ifndef __OP__
#define __OP__
#define def_op(op)\
this_type operator op (const this_type& a)const{this_type k(*this);k op##=a;return k;}
#define def_cmp(op,n2)\
bool operator op (const this_type& a)const{return n2 op a.n2;}
#define def_all_cmp(n2)\
def_cmp(<,n2) def_cmp(>,n2) def_cmp(<=,n2) def_cmp(>=,n2)\
def_cmp(!=,n2) def_cmp(==,n2)
#endif
template<class T,class R=ratio<1,10000000>>
struct _zfloat{
	using this_type=_zfloat;
	T v;
    static constexpr T x{(T)R::num/R::den};
	_zfloat()=default;
	_zfloat(T a):v(a){}
	_zfloat& operator+=(const _zfloat& a){return v+=a.v,*this;}
	_zfloat& operator-=(const _zfloat& a){return v-=a.v,*this;}
	_zfloat& operator*=(const _zfloat& a){return v*=a.v,*this;}
	_zfloat& operator/=(const _zfloat& a){return v/=a.v,*this;}
	def_op(+) def_op(-) def_op(*) def_op(/)
    bool operator==(const _zfloat& a)const{return abs(v-a.v)<=x;}
    bool operator!=(const _zfloat& a)const{return !operator==(a);}
    operator bool()const{return abs(v)>x;}
    def_cmp(<,v) def_cmp(>,v) def_cmp(<=,v) def_cmp(>=,v)
};
template<class T,class R>
ostream& operator<<(ostream& os,const _zfloat<T,R>& a){return os<<a.v;}
template<class T,class R>
istream& operator>>(istream& os,_zfloat<T,R>& a){T k;os>>k;a=_zfloat<T,R>(k);return os;}
using zfloat=_zfloat<float>;
using zdouble=_zfloat<double>;
using zldouble=_zfloat<long double>;