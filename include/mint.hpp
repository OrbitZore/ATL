template<class T,T mod>
struct _mint{
	T v;
	_mint()=default;
	_mint(const T &a){v=a%mod;}
	_mint(const _mint &a){v=a.v;}
	_mint& operator=(const _mint &a){return v=a.v,*this;}
	_mint& operator+=(const _mint a){return (v+=a.v)>mod&&(v-=mod),*this;}
	_mint& operator-=(const _mint a){return (v-=a.v)<0&&(v+=mod),*this;}
	_mint& operator*=(const _mint a){return (v*=a.v)%=mod,*this;}
	_mint operator+(const _mint a)const{_mint k(*this);k+=a;return k;}
	_mint operator-(const _mint a)const{_mint k(*this);k-=a;return k;}
	_mint operator*(const _mint a)const{_mint k(*this);k*=a;return k;}
	bool operator<(const _mint a)const{return v<a.v;}
	bool operator>(const _mint a)const{return v>a.v;}
	bool operator==(const _mint a)const{return v==a.v;}
	bool operator<=(const _mint a)const{return v<=a.v;}
	bool operator>=(const _mint a)const{return v>=a.v;}
};
template<class T,T mod>
ostream& operator<<(ostream& os,const _mint<T,mod>& a){return os<<a.v;}
template<int mod>
using mint=_mint<int,mod>;
template<ll mod>
using mll=_mint<ll,mod>;