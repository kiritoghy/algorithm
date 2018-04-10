#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;

struct egde{
	int v,w,next;
}e[100*100 + 5];
typedef pair<int ,int>pii;
bool vis[100 + 5];
int p[100 + 5],l[100 + 5],x[100 + 5];
int dis[100 + 5];
priority_queue<pii, vector<pii>, greater<pii> >q;
int ans = 0x3f3f3f3f;
int m,n;
int head[100 + 5],k = 1;

void adde(int u,int v,int w)
{
	e[k].v = v;
	e[k].w = w;
	e[k].next = head[u];
	head[u] = k++;
}
int abs(int a){
	return a <= 0 ? -a : a;
}
int dijkstra(int x)
{
	memset(dis,0x3f,sizeof(dis));
	memset(vis,0,sizeof(vis));
	dis[x] = p[x];q.push(make_pair(dis[x],x));vis[x] = 1;
	while(q.size()){
		int u = q.top().second;q.pop();
		for(int i = head[u]; i ; i = e[i].next){
			int v = e[i].v;
			if(abs(l[u] - l[v]) <= m && abs(l[x] - l[v]) <= m && (abs(l[v] - l[1]) <= m) && abs(l[u] - l[1]) <= m){
				if(dis[v] > dis[u] + e[i].w)
				dis[v] = dis[u] + e[i].w;
				if(!vis[v]){
					vis[v] = 1;
					q.push(make_pair(dis[v],v));
				}
			}
		}
	}
	return dis[1];
}
int main()
{
	while(~scanf("%d%d",&m,&n)){
		ans = 0x3f3f3f3f;
		for(int i = 1; i <= n; ++i){
			scanf("%d%d%d",&p[i],&l[i],&x[i]);
			for(int j = 1; j <= x[i]; ++j){
				int t,v;
				scanf("%d%d",&t,&v);
				adde(t,i,v);
			}
		}
		for(int i = 1; i <= n; ++i)
		ans = min(ans,dijkstra(i));
		if(ans == 0x3f3f3f3f)printf("%d\n",p[1]);
		else printf("%d\n",ans);
	}
	return 0;
}
