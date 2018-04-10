#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define maxn 100010
using namespace std;

int n,m;
int sz = -1;
struct node {
	node *ch[2];
	int v,s;
	bool rev;
	node(){
		//ch[0] = ch[1] = NULL;
		s = 0,v = 0,rev = 0;
	}
	int cmp(int k){
		int d = k - ch[0] -> s;
		if(d == 1)return -1;
		else return d <= 0 ? 0 : 1;
	}
	void maintain(){
		s = 1;
		if(ch[0] != NULL)s += ch[0] -> s;
		if(ch[1] != NULL)s += ch[1] -> s;
	}
	void pushdown(){
		if(rev){
			rev = 0;
			swap(ch[0],ch[1]);
			ch[0] -> rev = !ch[0] -> rev;
			ch[1] -> rev = !ch[1] -> rev;
		}
	}
}T[maxn], *null, *u;

node *build(int nm){
	if(!nm) return null;
	node *l = build(nm >> 1);
	node *o = &T[++sz];
	o -> v = sz;
	o -> ch[0] = l;
	o -> ch[1] = build((nm - 1) >> 1);
	o -> maintain();
	return o;
}
void rotate(node *& o,int d){//d == 0左旋 
	node *k = o -> ch[d ^ 1]; o -> ch[d ^ 1] = k -> ch[d]; k -> ch[d] = o;
	o -> maintain();k -> maintain(); o = k;
}
void splay(node *& o, int k){//是把o与子树交换 
	o -> pushdown();
	int d = o -> cmp(k);
	if(d == 1)k -= o -> ch[0] -> s + 1;
	if(d != -1){
		node *p = o -> ch[d];
		p -> pushdown();
		int d2 = p -> cmp(k);
		int k2 = (d2 == 0 ? k : k - p -> ch[0] -> s - 1);
		if(d2 != -1){
			splay(p -> ch[d2], k2);
			if(d == d2)rotate(o, d ^ 1);//共线 
			else rotate(o -> ch[d], d);
		}
		rotate(o, d ^ 1);
	}
}
void split(node *o,int k,node *& left, node *& right) {
	splay(o, k);
	left = o;
	right = o ->ch[1];
	o -> ch[1] = null;
	left -> maintain();
}
node *merge(node *left,node *right) {
	splay(left, left -> s);//旋到右子树为空
	left -> ch[1] = right;
	left -> maintain();
	return left;
}
void print(node *o){
	if(o != null){
		o -> pushdown();
		print(o -> ch[0]);
		if(o -> v)printf("%d\n", o -> v);
		print(o -> ch[1]);
	}
}
int main()
{
	while(~scanf("%d%d",&n,&m)){
		null = new node();
		node *mid,*left,*right,*root;
		root = build(n + 1);
		for(int i = 1; i <= m; ++i){
			int a,b;
			scanf("%d%d",&a,&b);
			split(root, a, left, u);
			split(u, b - a + 1, mid, right);
			mid -> rev ^= 1;
			root = merge(merge(left,right), mid);
		}
		print(root);
	}
	return 0;
}
