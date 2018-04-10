#include<cstdio>
#include<iostream>
#include<vector>
#include<cstring>
#include<cmath>
#define mem(a,x) memset(a, x, sizeof(a))
using namespace std;

vector<int >e[10000 + 5];
int pos[10000 + 5];//第一个出现的位置 
int depth[10005 << 1];//出现的深度
int dpmin[10005 << 1][30];//表示以i开始，持续2^j个最小值的下标 
int r[10005 << 1];//出现的顺序 
int ind[10000 + 5];//入度判断 
int root;
int T;
int n, m;

void init()
{
	m = 0;
	for(int i = 1; i <= n; i++)
	{
		ind[i] = 0;
		e[i].clear();
	}
	mem(pos, 0);
	mem(depth,0);
	mem(r, 0);
}
void dfs(int u, int deep)
{
	r[++m] = u;//访问到时进行记录 
	depth[m] = deep;
	if(!pos[u]) pos[u] = m;
	for(int i = 0; i < e[u].size(); i++)
	{
		dfs(e[u][i],deep + 1);
		r[++m] = u;//回溯时也记录 
		depth[m] = deep;
	}
}
void RMQ()
{
	for(int i = 1; i <= m; i++)
	dpmin[i][0] = i;
	for(int j = 1; (1 << j) <= m; j++)
	for(int i = 1; i <= m; i++)
		if(i + (1 << j) - 1 <= m)
		{
			if(depth[dpmin[i][j - 1]] < depth[dpmin[i + (1 << (j - 1))][j - 1]])
			dpmin[i][j] = dpmin[i][j - 1];
			else dpmin[i][j] = dpmin[i + (1 << (j - 1))][j - 1];
		}
}
int work(int a, int b)
{
	int l = pos[a], r1 = pos[b];
	if(l > r1)swap(l, r1);
	int k = (int)(log((double)(r1 - l + 1)) / log(2.0));
	if(depth[dpmin[l][k]] < depth[dpmin[r1 - (1 << k) + 1][k]]) return r[dpmin[l][k]];
	else return r[dpmin[r1 - (1 << k) + 1][k]];
}
int main()
{
	scanf("%d", &T);
	while(T--)
	{
		init();
		scanf("%d", &n);
		for(int i = 1; i < n; i++)
		{
			int u, v;
			scanf("%d%d", &u, &v);
			e[u].push_back(v);
			ind[v]++;
		}
		for(int i = 1; i <= n; i++)
		if(!ind[i]){
			root = i;break;
		}
		dfs(root,0);
		RMQ();
		int a, b;
		scanf("%d%d", &a, &b);
		printf("%d\n", work(a,b));
	}
	return 0;
}
