template<class T>
struct basic_gauss{
    using Vec=valarray<T>;
    vector<Vec> v;
    int _n;
    basic_gauss(int n):_n(n){}
    template<class U>
    void push_back(U&& a){v.push_back(forward<U>(a));}
    int solve(){
    	vector<int> x(_n,-1);
    	int ans=0;
    	auto f=[this](int i,int beg){return find_if(v.begin()+beg,v.end(),[=](const Vec &a){return a[i];});};
    	int ii=0;
        for (int i=0;i<_n;i++){
        	auto it=f(i,ii);
        	if (it==v.end()) continue;
        	else iter_swap(v.begin()+ii,it);
        	v[ii]/=(T)v[ii][x[ii]=i];
        	for (int j=ii+1;j<v.size();j++)
        		if (v[j][i]){
        			v[j]-=v[ii]*(T)v[j][i];
        		}
        	ans++;
        	ii++;
        }
        for (int i=ii-1;i>=0;i--){
        	for (int j=0;j<v.size();j++)
        		if (j!=i&&v[j][x[i]]){
        			v[j]-=v[i]*(T)v[j][x[i]];
        		}
        }
        return ans;
    }
};