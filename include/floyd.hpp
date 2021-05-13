template<class vT=int,class GT>
vector<vector<vT>> floyd(const GT &G){
	const auto n=G.size();
	vector<vector<vT>> dp(n,vector<vT>(n,INF));
	for (size_t i=0;i<n;i++) dp[i][i]=0;
	for (size_t k=0;k<n;k++)
		for (auto &e:G[k])
			cmin(dp[k][e.v],e.w);
	for (size_t k=0;k<n;k++)
		for (size_t i=0;i<n;i++)
			for (size_t j=0;j<n;j++)
				cmin(dp[i][j],dp[i][k]+dp[k][j]);
	return dp;
}