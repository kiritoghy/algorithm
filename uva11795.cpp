#include<cstdio>
#include<iostream>
#include<cstring>
#define ll long long
using namespace std;

int T;
int n;
int C[20][20];
ll dp[(1 << 16) + 5];
char s[20 + 5];
int vis[20];

int main()
{
	scanf("%d",&T);
	int count = 1;
	while(T--){
		memset(dp,0,sizeof(dp));
		scanf("%d",&n);
		getchar();
		for(int i = 0; i <= n; ++i){
			gets(s);
			for(int j = 0; j < n; ++j)
			C[i][j + 1] = s[j] - '0';
		}
		ll tot = 1 << n;
		dp[0] = 1;
		for(ll S = 0; S < tot; ++S){
			memset(vis,0,sizeof(vis));
			for(int j = 1; j <= n; ++j)
			if(S & (1 << (j - 1))){
				vis[j] = 1;
				for(int k = 1; k <= n; k++)
				if(C[j][k])vis[k] = 1;
			}
			for(int j = 1; j <= n; ++j){
				if((!(S & (1 << (j - 1)))) && (vis[j] || C[0][j])){
					dp[S | (1 << (j - 1))] += dp[S];
				}
			}
		}
		printf("Case %d: %lld\n",count++,dp[tot - 1]);
	}
	return 0;
}
