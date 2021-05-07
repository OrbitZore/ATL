template<class T,size_t n,size_t m>
struct Matrix:public valarray<valarray<T>>{
	using base1=valarray<T>;
	using base2=valarray<base1>;
	using base2::base2;
	Matrix(const T &a):base2(base1(a,m),n){}
	Matrix():base2(base1(m),n){}
};

template<class T,size_t n,size_t m>
Matrix<T,n,n> operator*(const Matrix<T,n,m> &a,const Matrix<T,m,n> &b){
	Matrix<T,n,n> x;
	for (size_t i=0;i<n;i++)
		for (size_t j=0;j<n;j++)
			for (size_t k=0;k<m;k++){
				x[i][j]+=a[i][k]*b[k][j];
			}
	return x;
}

template<class T,size_t n,size_t m>
Matrix<T,n,m> operator*(const Matrix<T,n,m> &a,const T &b){
	Matrix<T,n,m> x(a);
	for (size_t i=0;i<n;i++)
		for (size_t j=0;j<m;j++){
			x[i][j]*=b;
		}
	return x;
}