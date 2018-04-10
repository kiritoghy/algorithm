#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
struct egde{
	int u,v,w,next;
}e[1000*2+5];
const int inf=0x3fffffff;
int n,m;
int vis[200+5];
int dis[200+5];
int k=1,head[200+5];
int cot[200+5];
int s,t;
void adde(int u,int v,int w)
{
	e[k].v=v;
	e[k].w=w;
	e[k].next=head[u];
	head[u]=k++;
}
bool spfa()
{
	queue<int >q;
	q.push(s);
	vis[s]=1;
	dis[s]=0;
	while(q.size())
	{
		int u=q.front();q.pop();
		vis[u]=0;
		for(int i=head[u];i;i=e[i].next)
		{
			int v=e[i].v;
			if(dis[v]>dis[u]+e[i].w)
			{
				dis[v]=e[i].w+dis[u];
				if(!vis[v])
				{
					q.push(v);
					vis[v]=1;
					if(++cot[v]>n)
					{
						return false;
					}
				}
			}
		}
	}
	if(dis[t]==inf)return false;
	else return true;
}
int main()
{
	while(scanf("%d%d",&n,&m)&&n!=-1&&m!=-1)
	{
		memset(vis,0,sizeof(vis));
		memset(head,0,sizeof(head));
		memset(cot,0,sizeof(cot));
		for(int i=0;i<n;i++)dis[i]=inf;
		k=1;
		for(int i=1;i<=m;i++)
		{
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			adde(u,v,w);
			adde(v,u,w);
		}
		scanf("%d%d",&s,&t);
		if(spfa())printf("%d\n",dis[t]);
		else printf("-1\n");
		n=m=-1;
	}
	return 0;
}
