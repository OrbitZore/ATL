template<class T>
struct Complex{
    T x,y;
    Complex(T x=0,T y=0):x(x),y(y){}
    operator T(){return x;}
};
template<class T>
Complex<T> operator+(const Complex<T> a,const Complex<T> b){return Complex<T>(a.x+b.x,a.y+b.y);}
template<class T>
Complex<T> operator-(const Complex<T> a,const Complex<T> b){return Complex<T>(a.x-b.x,a.y-b.y);}
template<class T>
Complex<T> operator*(const Complex<T> a,const Complex<T> b){return Complex<T>(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
template<class T>
Complex<T> operator/(const Complex<T> a,const Complex<T> b){return Complex<T>(a.x*b.x+a.y*b.y,a.x*b.y-a.y*b.x)/(b.x*b.x+b.y*b.y);}
template<class T>
Complex<T>& operator+=(Complex<T> &a,const Complex<T> b){a.x+=b.x;a.y+=b.y;return a;}
template<class T>
Complex<T>& operator-=(Complex<T> &a,const Complex<T> b){a.x-=b.x;a.y-=b.y;return a;}
template<class T>
Complex<T>& operator*=(Complex<T> &a,const Complex<T> b){tie(a.x,a.y)=make_tuple(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);return a;}
template<class T>
Complex<T>& operator/=(Complex<T> &a,const Complex<T> b){tie(a.x,a.y)=make_tuple((a.x*b.x+a.y*b.y,a.x*b.y-a.y*b.x)/(b.x*b.x+b.y*b.y));return a;}
template<class T,template <class U> class complexT=Complex>
struct fft{
	static constexpr T Pi=M_PI;
	int size,l,n;
	vector<int> r;
	vector<complexT<T>> W[2];
	int floorintlog2(int i){
		int k=0;
		while (i) i>>=1,k++;
		return k;
	}
	fft(int size):size(size){
		l=floorintlog2(size);
		n=1<<l;
		r.resize(n,0);
		W[0].resize(n,{0,0});
		W[1].resize(n,{0,0});
	    for (int i=0;i<n;i++)
	        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	    for (int type:{0,1})
		    for (int i=0;i<n;i++)
		    	W[type][i]={cos(Pi/i),(type?1:-1)*sin(Pi/i)};
	}
	template<int type,class U>
	valarray<complexT<T>> _FFT(const U& B)const{
		using cT=complexT<T>;
		valarray<cT> A(n);
		copy(std::begin(B),std::end(B),begin(A));
	    for (int i=0;i<n;i++) 
	        if(i<r[i]) swap(A[i],A[r[i]]);
	    for (int mid=1;mid<n;mid<<=1){
	        const cT Wn=W[type][mid];
	        for (int R=mid<<1,j=0;j<n;j+=R){
	            cT w(1,0);
	            for (int k=0;k<mid;k++,w=w*Wn){
	                const cT x=A[j+k],y=w*A[j+mid+k];
	                A[j+k]=x+y;
	                A[j+mid+k]=x-y;
	            }
	        }
	    }
	    return A;
	}
	template<class U>
	valarray<complexT<T>> FFT(const U& A)const{return _FFT<0>(A);}
	template<class vT>
	valarray<vT> DFT(const valarray<complexT<T>>& A)const{
		auto b=_FFT<1>(A);
		valarray<vT> a(size);
		if (is_integral<vT>::value)
			for (int i=0;i<size;i++)
				a[i]=llround(b[i]/n);
		else
			for (int i=0;i<n;i++)
				a[i]=b[i]/n;
		return a;
	}
};