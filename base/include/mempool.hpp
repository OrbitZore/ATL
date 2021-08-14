constexpr unsigned long long operator "" _kb(unsigned long long i){return i*1024;}
constexpr unsigned long long operator "" _mb(unsigned long long i){return i*1024_kb;}
char pool[100_mb];unsigned long long pooli=0;
template<class T>
T* alloc(size_t i=1){
	auto pi=pooli;
	pooli+=i*sizeof(T);
	return (T*)(void*)&pool[pi];
}
void reset(){pooli=0;};
template<class T>
struct mallocator{
	typedef T value_type;
	mallocator() = default;
	template <class U> constexpr mallocator(const mallocator <U>&) noexcept {}
	[[nodiscard]] T* allocate(size_t n=1) {return alloc<T>(n);}
	void deallocate(T* p,size_t n) noexcept {}
};
 
template<class T, class U>
bool operator==(const mallocator<T>&,const mallocator<U>&) { return true; }
template<class T, class U>
bool operator!=(const mallocator<T>&,const mallocator<U>&) { return false; }
template<class T,class ...Args>
T* mnew(Args&&... args){
	return ::new((void*)(alloc<T>()))T(std::forward<Args>(args)...);
}
struct none_delete{
	constexpr none_delete()noexcept=default;
	template<class T>
	void operator()(T* p)const{};
};
template<template <class >class Allocator=allocator,class T>
T clone(const T& a){
	return T(&(*(Allocator<typename pointer_traits<T>::element_type>().allocate(1))=*a));
}