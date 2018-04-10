#include <cstring>
#include <iostream>
#include <cstdio>
#include <algorithm>
#define maxn 3000000
#define GETMID int mid = (l + r) >> 1
using namespace std;

int tcnt = 0;
int data[100000 + 5];
int a[100000 + 5];
struct node {
	int cnt;
	node *l, *r;
	node(){l = r = NULL; cnt = 0;}
}T[maxn], nil, *null = &nil;
node *root[100000 + 5];
int n,m;

inline node *Newnode(){
	T[tcnt].l = T[tcnt].r = null;
	return &T[tcnt++];
}
inline node *Copy(node *o) {
	node *tmp = Newnode();
	*tmp = *o;
	return tmp;
}
inline void build(node *o, int l,int r){
	if(l == r){
		o -> cnt = 0;
		return ;
	}
	
	GETMID;
	o -> l = Newnode();
	o -> r = Newnode();
	
	build(o -> l, l, mid);
	build(o -> r, mid + 1, r);
}
inline void insert(node *o, int l, int r, int a){
	++o -> cnt;
	if(l == r)return ;
	
	GETMID;
	if(a <= data[mid]){
		o -> l = Copy(o -> l);
		insert(o -> l, l, mid, a);
	}
	else{
		o -> r = Copy(o -> r);
		insert(o -> r, mid + 1, r, a);
	}
}
inline int Query(node *L, node *R, int l, int r, int k){
	if(l == r)return data[l];
	
	GETMID;
	int c = R -> l -> cnt - L -> l -> cnt;
	if(c >= k)return Query(L -> l, R -> l, l, mid, k);
	else return Query(L -> r, R -> r, mid + 1, r, k - c);
}
int main()
{
	while(~scanf("%d%d",&n ,&m)){
		tcnt = 0;
		for(int i = 1; i <= n; ++i){
			scanf("%d", &a[i]);
			data[i] = a[i];
		}
		sort(data + 1, data + 1 + n);
		int size = unique(data + 1, data + 1 + n) - (data + 1);
		
		root[0] = Newnode();
		build(root[0], 1, size);
		for(int i = 1; i <= n; ++i){
			root[i] = Copy(root[i - 1]);
			
			insert(root[i], 1, size, a[i]);
		}
		for(int i = 1; i <= m; ++i){
			int l,r,k;
			scanf("%d%d%d",&l, &r, &k);
			
			printf("%d\n", Query(root[l - 1], root[r], 1, size, k));
		}
	}
	
	return 0;
}
