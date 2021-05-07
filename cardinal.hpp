#include <bits/stdc++.h>
using INT=int;
#define int long long
#define pb push_back
#define eb emplace_back
using namespace std;
using ll=long long;
using vi=vector<int>;
using vll=vector<ll>;
using vvi=vector<vector<int>>;
using vvll=vector<vector<ll>>;
using pii=pair<int,int>;
using pll=pair<ll,ll>;
constexpr struct INF_t{
	#ifndef int
	constexpr operator int()const {return 0x3f3f3f3f;}
	#endif
	constexpr operator ll()const {return 0x3f3f3f3f3f3f3f3f;}
} INF;

template<class T>
auto _format(ostream &os,const char *c,T&& cv)->decltype(os<<cv,c+1){
	if (*++c=='.') os << setprecision(*++c-'0'+1);
	os << cv;
	while (*c!='}') c++;
	return c+1;
}
template<class T>
auto _format(ostream &os,const char *c,T&& cv)->decltype(begin(cv),c+1){
	const char *ct=c+1;
	size_t ic=0;
	for (auto &i:cv){
		const char *cc=c+1;
		while (*cc!='{'){
			if (*cc=='i') os << ic,cc++;
			else os << *cc++;
		}
		cc=_format(os,cc,i);
		while (*cc!='}') os << *cc++;
		ct=cc;
		ic++;
	}
	return ct+1;
}
string format(const char *c){return string(c);}
template<class T,class ...Args>
string format(const char *c,const T &a,Args&& ...rest){
	ostringstream os;
	while (*c!='{'&&*c!='\0') os<< *c++;
	if (*c=='{') c=_format(os,c,a);
	return os.str()+format(c,forward<Args>(rest)...);
}
template<class ...Args>
ostream& print(Args&& ...rest){return cout<<format(forward<Args>(rest)...);}
#ifdef LOCAL
#define debug(...) cerr<<format(...)
#else
#define debug(...) cerr
#endif
template<class T>
void _read(istream& is,T &a){is>>a;}
void _read(istream& is,ll &a){
    a=0;bool f=false;char c;
    while (!isdigit(c=is.get())&&is.good()) f=c=='-';
    if (!is.good()) return ;
    do a=(a<<3)+(a<<1)+c-'0'; while (isdigit(c=is.get()));
    if (f) a=-a;
}

void read(){}
template<class T,class ...Args>
void read(T& a,Args& ...args){_read(cin,a);read(args...);}
template<class T>
void reada(vector<T>& v,size_t n){
	v.reserve(n);
	for (size_t i=0;i<n;i++){
		T a;cin>>a;
		v.emplace_back(move(a));
	}
}
template<class T1,class T2>
bool cmin(T1 &a,const T2 b){return a>b?a=b,1:0;}
template<class T1,class T2>
bool cmax(T1 &a,const T2 b){return a<b?a=b,1:0;}
template<class T1,class T2,class ...T3>
bool cmin(T1 &a,const T2 b,const T3 ...rest){return cmin(a,b)|cmin(a,rest...);}
template<class T1,class T2,class ...T3>
bool cmax(T1 &a,const T2 b,const T3 ...rest){return cmax(a,b)|cmax(a,rest...);}

struct solution;

