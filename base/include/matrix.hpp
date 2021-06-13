template<class T,size_t n,size_t m>
struct matrix:public valarray<valarray<T>>{
	using base1=valarray<T>;
	using base2=valarray<base1>;
	using base2::base2;
	matrix(const T &a):base2(base1(a,m),n){}
	matrix():base2(base1(m),n){}
};

template<class T,size_t n,size_t m>
matrix<T,n,n> operator*(const matrix<T,n,m> &a,const matrix<T,m,n> &b){
	matrix<T,n,n> x;
	for (size_t i=0;i<n;i++)
		for (size_t j=0;j<n;j++)
			for (size_t k=0;k<m;k++)
				x[i][j]+=a[i][k]*b[k][j];
	return x;
}

template<class T,class U>
auto operator*(const valarray<T> &a,const U &b)->decltype(b+=1,a){
	valarray<T> x(a);
	for (auto &i:x) i*=b;
	return x;
}

template<class T,class U>
auto operator*=(valarray<T> &a,const U &b)->decltype(b+=1,a){
	for (auto &i:a) i*=b;
	return a;
}

template<class T,size_t n>
matrix<T,n,n> unitmatrix(){
	matrix<T,n,n> m;
	for (int i=0;i<n;i++) m[i][i]=1;
	return m;
}

template<class T,size_t n>
pair<bool,matrix<T,n,n>> inverse(matrix<T,n,n> a){
	auto b=unitmatrix<T,n>();
	for (int i=0;i<n-1;i++){
		int k=-1;
		for (int j=i;j<n;j++) if (a[j][i]!=0) {k=j;break;}
		if (k!=-1){
			swap(b[i],b[k]);swap(a[i],a[k]);
			for (int j=i+1;j<n;j++)
				if (a[k][i]!=0){
					T d=a[j][i]/a[k][i];
					a[j]-=a[k]*d;
					b[j]-=b[k]*d;
				}
		}else return {false,b};
	}
	for (int i=n-1;i>=0;i--){
		b[i]/=a[i][i];a[i]/=a[i][i];
		for (int j=i-1;j>=0;j--){
			b[j]-=b[i]*a[j][i];
			a[j]-=a[i]*a[j][i];
		}
	}
	return {true,b};
}