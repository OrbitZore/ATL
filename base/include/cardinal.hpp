#include <bits/stdc++.h>
using namespace std;
inline struct FAST_IO{
	inline FAST_IO(){
		ios_base::sync_with_stdio(false);
		cin.tie(NULL);
	}
}__fast_io;
#if __cplusplus < 201402L
template<class T, class U=T>
inline T exchange(T& obj, U&& new_value){
    T old_value=move(obj);
    obj=forward<U>(new_value);
    return old_value;
}
#endif
#define cons(a,...) a=typename decay<decltype(a)>::type(__VA_ARGS__)
using INT=int;
#define DEF_NUM(num) \
using i##num=int##num##_t;using u##num=uint##num##_t;
DEF_NUM(8)DEF_NUM(16)DEF_NUM(32)DEF_NUM(64)
#ifdef __SIZEOF_INT128__
using i128=__int128;using u128=unsigned __int128;
#endif
using usize=uintptr_t;using isize=intptr_t;
using f32=float;using f64=double;using f128=long double;
#define x first
#define y second
//#define int long long
#define pb push_back
#define eb emplace_back
#define ALL(a) (a).begin(),(a).end()
inline auto &_=std::ignore;
using ll=long long;
template<class T>
using vec=vector<T>;
template<bool B,class T=void>
using enableif_t=typename enable_if<B,T>::type;

#define DEF_COULD(name,exp) \
template<class U> \
struct name{\
	template<class T>\
	inline constexpr static auto is(int i)->decltype(exp,true){return true;}\
	template<class T>\
	inline constexpr static bool is(...){return false;}\
	inline static const bool value=is<U>(1);\
};
#define DEF_CAN(name,exp) DEF_COULD(can##name,exp)
#define ENABLE(T,name) enableif_t<can##name<T>::value>(1)
#define ENABLEN(T,name) enableif_t<!can##name<T>::value>(1)
#define FOR_TUPLE enableif_t<i!=tuple_size<T>::value>(1)
#define END_TUPLE enableif_t<i==tuple_size<T>::value>(1)
#define FOR_TUPLET(T) enableif_t<i!=tuple_size<T>::value>(1)
#define END_TUPLET(T) enableif_t<i==tuple_size<T>::value>(1)

#define DEF_INF(name,exp)\
constexpr inline struct{\
	template<class T>\
	inline constexpr operator T()const {return numeric_limits<T>::exp();}\
} name;

DEF_CAN(Out,(cout<<*(T*)(0))) DEF_CAN(For,begin(*(T*)(0)))
DEF_INF(INF,max) DEF_INF(MINF,min)
DEF_CAN(Array,declval<T>()[0])

template<size_t i,class T>
inline auto operator>>(istream& is,T &r)->decltype(END_TUPLE,is){
	return is;
}
template<size_t i=0,class T>
inline auto operator>>(istream& is,T &r)->decltype(FOR_TUPLE,is){
	is>>get<i>(r);
	return operator>> <i+1>(is,r);
}

template<size_t i,class ...Args>
inline auto operator>>(istream& is,const tuple<Args&...> &r)->decltype(END_TUPLET(tuple<Args&...>),is){
	return is;
}
template<size_t i=0,class ...Args>
inline auto operator>>(istream& is,const tuple<Args&...> &r)->decltype(FOR_TUPLET(tuple<Args&...>),is){
	is>>get<i>(r);
	return operator>> <i+1>(is,r);
}
namespace z3475{
template<class T>
inline auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLE(T,Out),c+1);
template<size_t i,class T>
inline auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLEN(T,For),END_TUPLE,c+1);
template<size_t i=0,class T>
inline auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLEN(T,For),FOR_TUPLE,c+1);
template<class T>
inline auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLEN(T,Out),ENABLE(T,For),c+1);


template<class T>
inline auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLE(T,Out),c+1){
	os << cv;
	while (*c!='}') c++;
	return c+1;
}
template<size_t i,class T>
inline auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLEN(T,For),END_TUPLE,c+1){
	return c;
}
template<size_t i,class T>
inline auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLEN(T,For),FOR_TUPLE,c+1){
	while (*c!='{') os << *c++;
	c=__format(os,c,get<i>(cv));
	return __format<i+1>(os,c,cv);
}
template<class T>
inline auto __format(ostream &os,const char *c,const T& cv)->decltype(ENABLEN(T,Out),ENABLE(T,For),c+1){
	const char *ct=c+1;
	if (cv.size()==0){
		int b=1;
		while (1){
			if (*ct=='}') b--;
			if (*ct=='{') b++;
			if (!b) break;
			ct++;
		}
	}else{
		for (auto &i:cv){
			const char *cc=c+1;
			while (*cc!='{') os << *cc++;
			cc=__format(os,cc,i);
			while (*cc!='}') os << *cc++;
			ct=cc;
		}
	}
	return ct+1;
}
inline void _format(ostream &os,const char *c){
	while (*c!='{'&&*c!='\0') os<< *c++;
}
template<class T,class ...Args>
inline void _format(ostream &os,const char *c,const T &a,const Args& ...rest){
	while (*c!='{'&&*c!='\0') os<< *c++;
	if (*c=='{') c=__format(os,c,a);
	_format(os,c,rest...);
}
template<class ...Args>
inline string format(const char *c,const Args& ...rest){
	ostringstream os;
	_format(os,c,rest...);
	return os.str();
}
template<class ...Args>
inline ostream& print(const char *c,const Args& ...rest){return _format(cout,c,rest...),cout;}
template<class ...Args>
inline ostream& println(const char *c,const Args& ...rest){return print(c,rest...)<<endl;}
}//namespace z3475
using namespace z3475;
#ifndef ONLINE_JUDGE
#define debug(...) cerr<<format(__VA_ARGS__)
#define debugln(...) cerr<<format(__VA_ARGS__)<<endl
#else
#define debug(...) cerr
#define debugln(...) cerr
#endif

template<class T>
inline uintptr_t flat(T* b){
	return reinterpret_cast<uintptr_t>(b);
}
template<class T>
inline auto index(const T a[],uintptr_t p)->decltype(ENABLEN(T,Array),tuple<int>()){
	return (p-flat(&a[0]))/sizeof(T);
}
template<class T>
inline auto index(const T a[],uintptr_t p)->decltype(ENABLE(T,Array),
	tuple_cat(tuple<int>(),index(a[0],p))){
	int i=(p-flat(a))/sizeof(a[0]);
	p-=i*sizeof(a[0]);
	return tuple_cat(tuple<int>(i),index(a[0],p));
}

template<class T,class ...Args>
struct Rtar{
	T& a;tuple<Args...> n;
	inline Rtar(T& a,tuple<Args...> n):a(a),n(n){}
};
template<class T,class ...Args>
inline Rtar<T,Args&...> rtar(T &a,Args&... rest){
	return Rtar<T,Args&...>(a,tie(rest...));
}
template<size_t i,class U,class ...Args,class T=tuple<Args&...>>
inline auto operator>>(istream& is,Rtar<U,Args&...> r)->decltype(END_TUPLE,is){
	return is>>r.a;
}
template<size_t i=0,class U,class ...Args,class T=tuple<Args&...>>
inline auto operator>>(istream& is,Rtar<U,Args&...> r)->decltype(FOR_TUPLE,is){
	r.a=typename decay<U>::type(get<i>(r.n));
	for (auto &w:r.a)
		operator>> <i+1>(is,Rtar<decltype(w),Args&...>(w,r.n));
	return is;
}
template<class T1,class T2>
inline bool cmin(T1 &a,const T2 b){return a>b?a=b,1:0;}
template<class T1,class T2>
inline bool cmax(T1 &a,const T2 b){return a<b?a=b,1:0;}
template<class T1,class T2,class ...T3>
inline bool cmin(T1 &a,const T2 b,const T3 ...rest){return cmin(a,b)|cmin(a,rest...);}
template<class T1,class T2,class ...T3>
inline bool cmax(T1 &a,const T2 b,const T3 ...rest){return cmax(a,b)|cmax(a,rest...);}

inline bool MULTIDATA=true;