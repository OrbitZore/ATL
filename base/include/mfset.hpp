struct mfset:protected vector<int>{
	mfset(){}
	mfset(int size){resize(size);}
	void resize(int size){
		vector<int>::resize(size);
		iota(this->begin(),this->end(),0);
	}
	int find(int a){
		int &b=this->operator[](a);
		return a==b?a:b=find(b);
	}
	void merge(int a,int b){
		int aa=find(a),bb=find(b);
		if (aa!=bb)
			this->operator[](bb)=aa;
	}
};