template<class T>
vector<int> to_next(T s){
	vector<int> next(s.size(),-1);
	next[0]=-1;
	for (int i=1;i<s.size();i++){
		int w=next[i-1];
		while (w!=-1&&s[w+1]!=s[i]) w=next[w];
		next[i]=(s[w+1]==s[i])+w;
	}
	return next;
}
template<class T>
vector<int> KMP(T a,T b){
	vector<int> pos;
	auto bn=to_next(b);
	int ai=0,bi=0;
	while (ai<=a.size()){
		if (bi!=b.size()&&a[ai]==b[bi]){
			ai++;bi++;
		}else{
			if (bi==b.size()){
				pos.push_back(ai-bi);
			}
			if (bi!=0){
				bi=bn[bi-1]+1;
			}else{
				ai++;
			}
		}
	}
	return pos;
}
