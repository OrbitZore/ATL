template<class T,class R=ratio<1,10000000>>
struct _zfloat{
	T v;
    static constexpr T x{(T)R::num/R::den};
	_zfloat()=default;
	_zfloat(T a):v(a){}
	_zfloat& operator+=(const _zfloat& a){return v+=a.v,*this;}
	_zfloat& operator-=(const _zfloat& a){return v-=a.v,*this;}
	_zfloat& operator*=(const _zfloat& a){return v*=a.v,*this;}
	_zfloat& operator/=(const _zfloat& a){return v/=a.v,*this;}
	op_zfloat(+) op_zfloat(-) op_zfloat(*) op_zfloat(/)
    bool operator==(const _zfloat& a)const{return abs(v-a.v)<=x;}
    bool operator!=(const _zfloat& a)const{return !operator==(a);}
    operator bool()const{return abs(v)>x;}
	cmp_zfloat(<) cmp_zfloat(>) cmp_zfloat(<=) cmp_zfloat(>=)
};
template<class T,class R>
ostream& operator<<(ostream& os,const _zfloat<T,R>& a){return os<<a.v;}
template<class T,class R>
istream& operator>>(istream& os,_zfloat<T,R>& a){T k;os>>k;a=_zfloat<T,R>(k);return os;}
using zfloat=_zfloat<float>;
using zdouble=_zfloat<double>;
using zldouble=_zfloat<long double>;