template<class T>
struct index_iterator:T{
	int i{0};
	index_iterator& operator++(){
		i++;T::operator++();
		return *this;
	}
	pair<int,decltype(declval<T>().T::operator*())> operator*(){return {i,this->T::operator*()};}
};
template<class T>
struct index_container_wrapper{
	T &a;
	using itT=decltype(a.begin());
	using iitT=index_iterator<itT>;
	iitT begin(){return iitT{a.begin()};}
	iitT end(){return iitT{a.end()};}
};
template<class T>
index_container_wrapper<T> iter(T &a){return {a};}