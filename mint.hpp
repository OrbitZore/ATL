template<class T,T mod>
struct mint{
	T v;
	mint()=default;
	mint(const T &a){v=a%mod;}
	mint(const mint &a){v=a.v;}
	mint& operator=(const mint &a){return v=a.v,*this;}
	mint& operator+=(const mint a){return (v+=a.v)>mod&&(v-=mod),*this;}
	mint& operator-=(const mint a){return (v-=a.v)<0&&(v+=mod),*this;}
	mint& operator*=(const mint a){return (v*=a.v)%=mod,*this;}
	mint operator+(const mint a)const{mint k(*this);k+=a;return k;}
	mint operator-(const mint a)const{mint k(*this);k-=a;return k;}
	mint operator*(const mint a)const{mint k(*this);k*=a;return k;}
	bool operator<(const mint a)const{return v<a.v;}
	bool operator>(const mint a)const{return v>a.v;}
	bool operator==(const mint a)const{return v==a.v;}
	bool operator<=(const mint a)const{return v<=a.v;}
	bool operator>=(const mint a)const{return v>=a.v;}
};
template<class T,T mod>
ostream& operator<<(ostream& os,const mint<T,mod>& a){return os<<a.v;}