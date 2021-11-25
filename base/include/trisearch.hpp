template<class T,class T2>
auto tribound(T a,T b,T2 func)->decltype(
enableif_t<is_floating_point<T>::value>(1),
func(a)){
	T w=(b-a)/3;
	while (b-a>=1e-7){
		T aa,bb;
		auto a1=func(aa=a+w),a2=func(bb=b-w);
		if (a1<=a2) a=aa;
		if (a1>=a2) b=bb;
	}
	return (a+b)/2;
}
template<class T,class T2>
auto tribound(T a,T b,T2 func)->decltype(
enableif_t<is_integral<T>::value>(1),
func(a)){
	T w;
	while (w=(b-a)/3){
		T aa,bb;
		auto a1=func(aa=a+w),a2=func(bb=b-w);
		if (a1<=a2) a=aa;
		if (a1>=a2) b=bb;
	}
	auto y=func(a);
	T x=a;
	for (T i=a+1;i<=b;i++)
		if (cmax(y,func(i)))
			x=i;
	return x;
}