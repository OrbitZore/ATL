//max_element
template<class T,class cmp=less<T>,class IT=int>
struct mono_queue{
	deque<pair<IT,T>> q;
	IT l={0},r={0};
	void push(T a){
		while (q.size()&&!cmp()(a,q.back().second)) q.pop_back();
		q.push_back({r++,a});
	}
	void pop(){
		if (q.front().first==l) q.pop_front();
		l++;
	}
	T get()const{
		return q.front().second;
	}
};
