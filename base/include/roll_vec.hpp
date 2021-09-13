template<class T,size_t len,class IT=int>
struct roll_vec:private vector<T>{
	using vector<T>::vector;
	array<vector<T>,len> a{static_cast<const vector<T>&>(*this)};
	IT bas=0;
	vector<T>& operator[](IT i){return a[(bas+i+len)%len];}
	const vector<T>& operator[](IT i)const{return a[(bas+i+len)%len];}
	void next(){if (++bas==len) bas-=len;a[bas]=static_cast<const vector<T>&>(*this);}
};