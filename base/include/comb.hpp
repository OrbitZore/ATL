template<class T,size_t sz=1000>
struct combr{
	T fac[sz];
	combr(){
		fac[0]=1;
		for (size_t i=1;i<sz;i++)
			fac[i]=fac[i-1]*i;
	}
	T C(int n,int r){
		return r>n?0:fac[n]/fac[r]/fac[n-r];
	}
	T A(int n,int r){
		return r>n?0:fac[n]/fac[n-r];
	}
};