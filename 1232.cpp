#include<iostream>
#include<cstdio>
using namespace std;
int fa[1000 + 10];
int n,m;
int find(int x)
{
	//return fa[x] == x ? x : fa[x] = find(fa[x]);
	if(fa[x] == x)return x;
	else return fa[x] = find(fa[x]);
}
int main()
{
	//freopen("x.in","r",stdin);
	while(scanf("%d%d",&n,&m) != EOF && n)
	{	
		int ans = 0;
		if(m == 0)
		{
			printf("%d\n", n - 1);
			continue;
		}
		for(int i = 1; i <= n; i++)
		fa[i] = i;
		for(int i = 1; i <= m; i++)
		{
			int a, b;
			scanf("%d%d",&a, &b);
			int x = find(a), y = find(b);
			if(x != y)
			{
				fa[x] = y;
			}
		}
		for(int i = 1; i <= n; i++)
		if(fa[i] == i)ans++;
		printf("%d\n",ans - 1);
	}
	return 0;
}
