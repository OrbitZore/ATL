#define ATL_MATH
constexpr ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
constexpr ll lcm(ll a,ll b){return a*b/gcd(a,b);}
template<class T>
T power(T a,size_t b,const T &unit=1){
	if (b==0) return unit;
	if (b&1) return a*power(a*a,b>>1,unit);
	return power(a*a,b>>1,unit);
}
constexpr ll ceildiv(const ll a,const ll b){return a/b+(a%b?1:0);}
tuple<ll,ll,ll> exgcd(ll a,ll b){//a1+b2=gcd(a,b)
	if (b==0) return make_tuple(a,1,0);
	ll g,x,y;
	tie(g,x,y)=exgcd(b,a%b);
	return make_tuple(g,y,x-a/b*y);
}
tuple<ll,ll,ll> Fexgcd(ll a,ll b){//a1+b2=gcd(a,b),ensure 1>0
	auto k=exgcd(a,b);
	if (get<1>(k)<0) {
		get<1>(k)+=b;
		get<2>(k)-=a;
	}
	return k;
}