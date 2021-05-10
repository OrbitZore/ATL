template <size_t n>
struct Primes{
	bitset<n> book;
	array<size_t,n> phi;
	vector<size_t> pri;
	Primes(){
		phi[1]=1;
		for (size_t i=2;i<n;i++){
			if (!book[i]) {
				phi[i]=i-1;
				pri.pb(i);
			}
			for (size_t j=0;j<pri.size();++j) {
				size_t w=i*pri[j];
				if (w>=n) break;
				book[w]=1;
				if (i%pri[j]) {
					phi[w]=phi[i]*(pri[j]-1);
				} else {
					phi[w]=phi[i]*pri[j];
					break;
				}
			}
		}
	}
	template <class T>
	bool is(const T &a)const{return book[a];}
	ll operator[](const size_t &i)const{return pri[i];}
};
Primes<100000> primes;