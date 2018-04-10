#include<cstdio>
#include<iostream>
#include<cstring>
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1
using namespace std;
int k;
int n;
char od[10+2];
int sum[50000<<2];
void pushup(int rt)
{
	sum[rt]=sum[rt<<1]+sum[rt<<1|1];
}
void build(int l,int r,int rt)
{
	if(l==r)scanf("%d",&sum[rt]);
	else
	{
		int m=(l+r)>>1;
		build(lson);
		build(rson);
		pushup(rt);
	}
}
void update(int pos,int add,int l,int r,int rt)
{
	if(l==r)sum[rt]+=add;
	else 
	{
		int m=(l+r)>>1;
		if(pos<=m)update(pos,add,lson);
		else update(pos,add,rson);
		pushup(rt);
	}
}
int query(int l1,int r1,int l,int r,int rt)
{
	if(l1<=l&&r1>=r)return sum[rt];
	else
	{
		int m=(l+r)>>1;
		int rec=0;
		if(l1<=m) rec+= query(l1,r1,lson);
		if(r1>m) rec+= query(l1,r1,rson);
		return rec;
	}
}
int main()
{
	//freopen("x.in","r",stdin);
	cin>>k;
	for(int i=1;i<=k;i++)
	{
		//memset(sum,0,sizeof(sum));
		printf("Case %d:\n",i);
		scanf("%d",&n);
		build(1,n,1);
		while(scanf("%s",od)&&strcmp(od,"End")!=0)
		{
			if(strcmp(od,"Add")==0)
			{
				int pos,add;
				scanf("%d%d",&pos,&add);
				update(pos,add,1,n,1);
			}
			if(strcmp(od,"Sub")==0)
			{
				int pos,add;
				scanf("%d%d",&pos,&add);
				update(pos,-1*add,1,n,1);
			}
			if(strcmp(od,"Query")==0)
			{
				int l1,r1;
				scanf("%d%d",&l1,&r1);
				cout<<query(l1,r1,1,n,1)<<endl;
			}
		}
	}
	return 0;
}
