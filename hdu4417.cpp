#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
#define GETMID int mid = (l + r) >> 1
using namespace std;

int cnt = 0, tcnt = 0;
int n, m;
int data[100000 + 5], a[100000 + 5];
int TT;
struct node {
	int cnt;
	node *l, *r;
	inline void init(){l = r = NULL; cnt = 0;}
}*root[100000 + 5], T[100000 * 25];

inline node *newnode(){
	T[tcnt].init();
	return &T[tcnt++];
}
inline int Get(int x){
	int ans = lower_bound(data + 1, data + 1 + cnt, x) - data;
	return ans - (x != data[ans]);
}
inline node* Copy(node *u){
	node *tmp = newnode();
	*tmp = *u;
	return tmp;
}
void build(node *u, int l, int r){
	if(l == r){
		u -> cnt = 0;
		return ;
	}
	
	GETMID;
	u -> l = newnode();
	u -> r = newnode();
	
	build(u -> l, l, mid);
	build(u -> r, mid + 1, r);
}
void insert(node *u, int pos, int l, int r){
	++u -> cnt;
	if(l == r)return ;
	
	GETMID;
	if(pos <= mid){
		u -> l = Copy(u -> l);
		insert(u -> l, pos, l, mid);
	}
	else {
		u -> r = Copy(u -> r);
		insert(u -> r, pos, mid + 1, r);
	}
}
int Query(node *a, node *b,int l, int r, int k){
	if(r <= k){
		return b -> cnt - a -> cnt;
	}
	else if(l <= k){
		GETMID;
		return Query(a -> l, b -> l, l, mid, k) + Query(a -> r, b -> r, mid + 1, r, k);
	}
	else return 0;
}
int main()
{
	int cas = 0;
	scanf("%d", &TT);
	
	while(TT--){
		scanf("%d%d", &n, &m);
		tcnt = cnt = 0;
		for(int i = 1; i <= n; ++i){
			scanf("%d", &a[i]);
			data[i] = a[i];
		}
		sort(data + 1, data + 1 + n);
		
		cnt = unique(data + 1, data + 1 + n) - (data + 1);
		root[0] = newnode();
		build(root[0], 1, cnt);
		
		for(int i = 1; i <= n; ++i){
			root[i] = Copy(root[i - 1]);
			insert(root[i], Get(a[i]), 1, cnt);
		}
		printf("Case %d:\n", ++cas);
		int l, r, h;
		for(int i = 1; i <= m; ++i){
			scanf("%d%d%d", &l, &r, &h);
			printf("%d\n",Query(root[l], root[r + 1], 1, cnt, Get(h)));
		}
	}
	return 0;
}
