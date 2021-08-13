template<class T>
struct ntt{
	int size,l,n;
	vector<int> r;
	const int mod{998244353};
	const array<const T,2> P{3,332748118};
	array<vector<T>,2> W;
	int floorintlog2(int i){
		int k=0;
		while (i) i>>=1,k++;
		return k;
	}
	ntt(int size):size(size){
		l=floorintlog2(size);
		n=1<<l;
		r.resize(n,0);
		W.fill(vector<T>(n));
	    for (int i=0;i<n;i++)
	        r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	    for (int type:{0,1})
		    for (int i=0;i<l;i++)
		    	W[type][i]=power(P[type],(mod-1)/(1<<i<<1));
	}
	template<int type,class U>
	valarray<T> _NTT(const U& B)const{
		valarray<T> A(n);
		copy(std::begin(B),std::end(B),begin(A));
	    for (int i=0;i<n;i++) 
	        if(i<r[i]) swap(A[i],A[r[i]]);
	    for (int mid=1,midj=0;mid<n;mid<<=1,midj++){
	        T Wn=W[type][midj];
	        for (int R=mid<<1,j=0;j<n;j+=R){
	            T w=1;
	            for (int k=0;k<mid;k++,w*=Wn){
	                const T x=A[j+k],y=w*A[j+mid+k];
	                A[j+k]=x+y;
	                A[j+mid+k]=x-y;
	            }
	        }
	    }
	    if (type) A*=power(T(n),mod-2);
	    return A;
	}
	template<class U>
	valarray<T> NTT(const U& A)const{return _NTT<0>(A);}
	valarray<T> DNT(const valarray<T>& A)const{return _NTT<1>(A);}
};