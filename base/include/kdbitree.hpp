template<class T>
T lowbit(T a){return a&(-a);}
template<class T,size_t n,size_t d,size_t i=0>
struct kdbitree{
    kdbitree<T,n,d,i+1> a[n];
    void add(const array<int,d>& ax,T v){
    	auto x=ax[i];
        while (x<n) a[x].add(ax,v),x+=lowbit(x);
    }
    T sum(const array<int,d>& ax){
        T ans=0;
    	auto x=ax[i];
        while (x>0) ans+=a[x].sum(ax),x-=lowbit(x);
        return ans;
    }
};
template<class T,size_t n,size_t d>
struct kdbitree<T,n,d,d>{
    T a;
    kdbitree():a(0){}
    void add(const array<int,d>& ax,T v){a+=v;}
    T sum(const array<int,d>& ax){return a;}
};