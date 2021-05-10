ll gcd(ll a,ll b){return b?gcd(b,a%b):a;}
ll lcm(ll a,ll b){return a*b/gcd(a,b);}
template<class T>
T power(T a,size_t b,const T &unit=1){
	if (b==0) return unit;
	if (b&1) return a*power(a*a,b>>1,unit);
	return power(a*a,b>>1,unit);
}
ll ceildiv(ll a,ll b){return a/b+(a%b?1:0);}
tuple<ll,ll,ll> exgcd(ll a,ll b){
	if (b==0) return {a,1,0};
	ll g,x,y;
	tie(g,x,y)=exgcd(b,a%b);
	return make_tuple(g,y,x-a/b*y);
}
