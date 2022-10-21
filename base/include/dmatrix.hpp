
#define for_n(i,n,exp) for (int i=0;i<n;i++) exp;
template<class T>
struct dmat:public vector<T>{
	int n,m;
	dmat(int n,int m):n(n),m(m),vector<T>(n*m,0){}
	dmat(int n,int m,initializer_list<T> a):n(n),m(m),vector<T>(a){}
	T* operator[](int i){return &vector<T>::operator[](i*m);}
	const T* operator[](int i)const{return &vector<T>::operator[](i*m);}
	dmat operator*(const dmat<T> &b)const{
		auto& a=(*this);
		dmat<T> x(a.n,b.m);
		for (size_t i=0;i<a.n;i++)
			for (size_t j=0;j<b.m;j++)
				for (size_t k=0;k<a.m;k++)
					x[i][j]+=a[i][k]*b[k][j];
		return *x;
	}
	dmat operator*=(const dmat<T> &b){return (*this)=(*this)*b;}
	static dmat<T> unit(int n,int m){
		dmat<T> x(n,m);
		for (int i=0;i<n;i++) x[i][i]=1;
		return x;
	}
};

template<class T>
pair<bool,dmat<T>> inv(dmat<T> a){
	int& n=a.n;
	auto b=dmat<T>::unit(n,n);
	for (int i=0;i<n-1;i++){
		int k=-1;
		for (int j=i;j<n;j++) if (a[j][i]) {k=j;break;}
		if (k!=-1){
    		for_n(j,n,(swap(a[i][j],a[k][j]),swap(b[i][j],b[k][j])));
			for (int j=i+1;j<n;j++)
				if (a[k][i]!=0){
					T d=a[j][i]/a[k][i];
					for_n(l,n,((a[j][l]-=a[k][l]*d),(b[j][l]-=b[k][l]*d)));
				}
		}else return {false,b};
	}
	for (int i=n-1;i>=0;i--){
		T aii=a[i][i];
		for_n(l,n,((b[i][l]/=aii),a[i][l]/=aii));
		for (int j=i-1;j>=0;j--){
			T aji=a[j][i];
			for_n(l,n,((a[j][l]-=a[i][l]*aji),(b[j][l]-=b[i][l]*aji)));
		}
	}
	return {true,b};
}

template<class T>
T det(dmat<T> a){
	int& n=a.n;
	vector<int> x(n,-1);
	int ans=0,ii=0;
    T D=1;
    for (int i=0;i<n;i++){
    	int it=-1;
		for (int j=i;j<n;j++) if (a[j][ii]) {it=j;break;}
    	if (it==-1) continue;
    	for_n(i,n,swap(a[ii][i],a[it][i]));
    	auto d=a[ii][x[ii]=i];
    	for_n(i,n,a[ii][i]/=d);
    	D*=d;
    	for (int j=ii+1;j<n;j++)
    		if (a[j][i]){
    			T d=a[j][i];
		    	for_n(k,n,a[j][k]-=a[ii][k]*d);
    		}
    	ans++;
    	ii++;
    }
    return ans!=n?0:D;
}