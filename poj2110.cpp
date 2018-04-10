#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

int mp[1000 + 5][1000 + 5];
bool vis[1000 + 5][1000 + 5];
int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
int ans = 0x3f3f3f3f;
int n; 

bool dfs(int L,int R,int x,int y){
	if(x == n && y == n)return 1;
	for(int i = 0; i < 4; ++i){
		int xx = x + dx[i];
		int yy = y + dy[i];
		if(xx < 1 || xx > n || yy < 1 || yy > n)continue;
		if(vis[xx][yy])continue;
		if(mp[xx][yy] >= L && mp[xx][yy] <= R){
			vis[xx][yy] = 1;
			if(dfs(L,R,xx,yy))return 1;
		}
	}
	return 0;
}
int main()
{
	//freopen("D.in", "r", stdin);
	//freopen("D.out", "w", stdout);
	while(~scanf("%d",&n)){
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j)
			scanf("%d",&mp[i][j]);
		}
		ans = 0x3f3f3f3f;
		int l = -1,r = 110;//(l,R]
		while(l < r - 1){
			int m = l + ((r - l) >> 1);
			int minn = mp[1][1] - m < 0 ? 0 : mp[1][1] - m;
			bool flag = 0;
			for(int i = minn; i <= mp[1][1]; ++i){
				memset(vis,0,sizeof(vis));
				vis[1][1] = 1;
				if(dfs(i,i + m,1,1)){
					flag = 1;
					break;
				}
			}
			if(flag){
				ans = min(ans,m);
				r = m;
			}
			else l = m;
		}
		printf("%d\n",ans);
	}
	return 0;
}
