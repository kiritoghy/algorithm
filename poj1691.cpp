#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
//#define DEBUG
using namespace std;

int vis[20];
int ans = 0x3f3f3f3f;
struct ret{
	int x1,y1;
	int x2,y2;
	int col;
}e[20];
int t;
int n;
int pre[100];
vector<int >out[20];
int in[20];

bool check(int i){
	if(vis[i])return false;
	if(in[i])return false;
	return true;
}
void dfs(int depth,int cnt,int c){
	if(depth == n){
		if(ans > cnt)ans = cnt;
		#ifdef DEBUG
		printf("cnt: %d\n",cnt);
		printf("%d ",x);
		for(int i = pre[x]; i ; i = pre[i])
		printf("%d ",i);
		printf("\n");
		#endif
		return ;
	}
	if(cnt > ans)return ;
	for(int i = 1; i <= n; ++i){
		if(check(i)){
			vis[i] = 1;
			for(int j = 0; j < out[i].size(); ++j)
			in[out[i][j]]--;
			#ifdef DEBUG
			pre[i] = x;
			#endif
			if(e[i].col == c || c == 0)
			dfs(depth + 1,cnt,e[i].col);
			else 
			dfs(depth + 1,cnt + 1, e[i].col);
			vis[i] = 0;
			for(int j = 0; j < out[i].size(); ++j)
			in[out[i][j]]++;
		}
	}
}
int main()
{
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		ans = 0x3f3f3f3f;
		memset(in,0,sizeof(in));
		memset(vis,0,sizeof(vis));
		for(int i = 1; i <= n; ++i)out[i].clear();
		for(int i = 1; i <= n; ++i)
			scanf("%d%d%d%d%d",&e[i].y1,&e[i].x1,&e[i].y2,&e[i].x2,&e[i].col);
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j){
				if(i == j)continue;
				if(e[i].y1 == e[j].y2){
					if(e[i].x1 >= e[j].x1 && e[i].x2 <= e[j].x2){
						in[i]++;
						out[j].push_back(i);
					}
					else if(e[i].x2 >= e[j].x1 && e[i].x2 <= e[j].x2){
						in[i]++;
						out[j].push_back(i);
					}
					else if(e[i].x1 <= e[j].x1 && e[i].x2 >= e[j].x2){
						in[i]++;
						out[j].push_back(i);
					}
				}
			}
		}
		dfs(0,1,0);
		printf("%d\n",ans);
	}
	return 0;
}
