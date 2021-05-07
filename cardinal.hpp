#include <bits/stdc++.h>
using INT=int;
//#define int long long
#define pb push_back
#define eb emplace_back
#define all(a) (a).begin(),(a).end()
using namespace std;
auto &_=std::ignore;
using ll=long long;
using vi=vector<int>;
using vll=vector<ll>;
using vvi=vector<vector<int>>;
using vvll=vector<vector<ll>>;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
constexpr struct{
	template<class T>
	constexpr operator T()const {return numeric_limits<T>::max();}
} INF;
constexpr struct{
	template<class T>
	constexpr operator T()const {return numeric_limits<T>::min();}
} MINF;
template<class T>
auto __format(ostream &os,const char *c,const T& cv)->decltype(os<<cv,c+1){
	os << cv;
	while (*c!='}') c++;
	return c+1;
}
template<size_t i,class T>
auto __format(ostream &os,const char *c,const T& cv)->decltype(
typename enable_if<i==tuple_size<T>::value>::type(1),c+1){return c;}
template<size_t i=0,class T>
auto __format(ostream &os,const char *c,const T& cv)->decltype(
typename enable_if<i!=tuple_size<T>::value>::type(1),c+1){
	while (*c!='{') os << *c++;
	c=__format(os,c,get<i>(cv));
	return __format<i+1>(os,c,cv);
}
template<class T>
auto __format(ostream &os,const char *c,const T& cv)->decltype(begin(cv),c+1){
	const char *ct=c+1;
	size_t ic=0;
	for (auto &i:cv){
		const char *cc=c+1;
		while (*cc!='{'){
			if (*cc=='i') os << ic,cc++;
			else os << *cc++;
		}
		cc=__format(os,cc,i);
		while (*cc!='}') os << *cc++;
		ct=cc;
		ic++;
	}
	return ct+1;
}
void _format(ostream &os,const char *c){
	while (*c!='{'&&*c!='\0') os<< *c++;
}
template<class T,class ...Args>
void _format(ostream &os,const char *c,const T &a,Args&& ...rest){
	while (*c!='{'&&*c!='\0') os<< *c++;
	if (*c=='{') c=__format(os,c,a);
	_format(os,c,forward<Args>(rest)...);
}
template<class ...Args>
string format(const char *c,Args&& ...rest){
	ostringstream os;
	_format(os,c,forward<Args>(rest)...);
	return os.str();
}
template<class ...Args>
ostream& print(const char *c,Args&& ...rest){return _format(cout,c,forward<Args>(rest)...),cout;}

#ifdef LOCAL
#define debug(...) cerr<<format(__VA_ARGS__)
#else
#define debug(...) cerr
#endif
template<class T,class ...Args>
struct Rtar{
	T& a;const tuple<Args...> n;
	Rtar(T& a,const tuple<Args...> n):a(a),n(n){}
};
template<class T,class ...Args>
Rtar<T,Args...> rtar(T &a,Args... rest){
	return Rtar<T,Args...>(a,make_tuple(rest...));
}
template<size_t i,class T,class ...Args>
auto operator>>(istream& is,Rtar<T,Args...> r)->decltype(
typename enable_if<i==tuple_size<decltype(r.n)>::value>::type(1),is){
	return is>>r.a;
}
template<size_t i=0,class T,class ...Args>
auto operator>>(istream& is,Rtar<T,Args...> r)->decltype(
typename enable_if<i!=tuple_size<decltype(r.n)>::value>::type(1),is){
	using OT=typename decay<decltype(r.a)>::type::value_type;
	auto inserter=back_inserter(r.a);
	for (size_t j=0;j<get<i>(r.n);j++){
		OT w;
		operator>> <i+1>(is,Rtar<OT,Args...>(w,r.n));
		inserter=w;
	}
	return is;
}

template<size_t i,class T>
auto operator>>(istream& is,T &r)->decltype(
typename enable_if<i==tuple_size<T>::value>::type(1),is){return is;}
template<size_t i=0,class T>
auto operator>>(istream& is,T &r)->decltype(
typename enable_if<i!=tuple_size<T>::value>::type(1),is){
	is>>get<i>(r);
	return operator>> <i+1>(is,r);
}

template<class T,class funcT>
auto operator *(T&& a,funcT func)
->typename decay<decltype(func(*begin(a)))>::type{
	for (auto i=begin(a),j=i;i!=end(a);i=j){
		if (++j==end(a)) return move(func(*i));
		else func(*i);
	}
}

template<class T,class funcT>
auto operator *(T&& a,funcT func)
->typename decay<decltype(func(a))>::type{
	return move(func(a));
}

template<class T,class funcT>
auto operator /(T&& a,funcT func)
->decltype(func(*begin(a)),a){
	for (auto &i:a) func(i);
	return a;
}

template<class T,class funcT>
auto operator /(T&& a,funcT func)
->decltype(func(a),a){
	func(a);
	return a;
}

template<class T1,class T2>
bool cmin(T1 &a,const T2 b){return a>b?a=b,1:0;}
template<class T1,class T2>
bool cmax(T1 &a,const T2 b){return a<b?a=b,1:0;}
template<class T1,class T2,class ...T3>
bool cmin(T1 &a,const T2 b,const T3 ...rest){return cmin(a,b)|cmin(a,rest...);}
template<class T1,class T2,class ...T3>
bool cmax(T1 &a,const T2 b,const T3 ...rest){return cmax(a,b)|cmax(a,rest...);}
