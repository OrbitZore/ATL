#define TEMP_ARR template<class T,size_t d,class T2,class TU=decltype(declval<T>()+declval<T2>())>
#define op_array(x) \
TEMP_ARR array<T,d>& operator x##=(array<T,d>& a,const array<T2,d>& b){for (size_t i=0;i<d;i++) a[i] x##=b[i];return a;}\
TEMP_ARR array<T,d>& operator x##=(array<T,d>& a,const T2& b){for (size_t i=0;i<d;i++) a[i] x##=b;return a;}\
TEMP_ARR array<TU,d> operator x(const array<T,d>& a,const array<T2,d>& b){array<TU,d> c;for (size_t i=0;i<d;i++) c[i]=a[i] x b[i];return c;}\
TEMP_ARR array<TU,d> operator x(const array<T,d>& a,const T2& b){array<TU,d> c;for (size_t i=0;i<d;i++) c[i]=a[i] x b;return c;}

op_array(+) op_array(-) op_array(*) op_array(/)
template<class T>
using vec2=array<T,2>;
template<class T>
using vec3=array<T,3>;
template<class T,size_t d>
T dot(const array<T,d>& a,const array<T,d>& b){
	T c=0;
	for (auto& i:a*b) c+=i;
	return c;
}
template<class T,size_t d>
double _abs(const array<T,d>& a){return sqrt(dot(a,a));}
template<class T,size_t d>
double normal(const array<T,d>& a){return a/abs(a);}
template<class T>
T crs(const vec2<T> &a,const vec2<T> &b){return a[0]*b[1]-a[1]*b[0];}
template<class T>
vec3<T> crs(const vec3<T> &a,const vec3<T> &b){return {a[1]*b[2]-a[2]*b[1],a[2]*b[0]-a[0]*b[2],a[0]*b[1]-a[1]*b[0]};}
template<class T,size_t d>
istream& operator>>(istream& is,array<T,d> &p){
	copy_n(istream_iterator<T>(is),d,p.begin());
	return is;
}