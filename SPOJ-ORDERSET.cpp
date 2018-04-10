#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

struct node{
	int v,pri,size;
	node* ch[2];
	node(int v = 0):v(v){
	 	ch[0] = ch[1] = NULL;
	 	pri = rand();
		size = 1;
	} 
	int cmp(int x){
		if(v == x)return -1;
		return x < v ? 0 : 1;
	}
	void maintain(){
		size = 1;
		if(ch[0] != NULL) size += ch[0] -> size;
		if(ch[1] != NULL) size += ch[1] -> size;
	}
};
int n;

void rotate(node* &o, int d){//d = 0代表左旋，1代表右旋 
	node* k = o -> ch[d ^ 1];
	o -> ch[d ^ 1] = k -> ch[d];
	k -> ch[d] = o;
	o -> maintain();k -> maintain();
	o = k;
}
int Count(node* &o,int x){
	if(o == NULL)return 0;
	int lsize;
	if(o -> ch[0] != NULL)lsize = o -> ch[0] -> size;
	else lsize = 0;
	if(x == o -> v)return lsize;
	else if(x < o -> v)return Count(o -> ch[0], x);
	else return lsize + 1 + Count(o -> ch[1], x);
}
int Find_kth(node* &o,int k){
	if(o == NULL || o -> size < k)return -1;
	int lsize;
	if(o -> ch[0] != NULL)lsize = o -> ch[0] -> size;
	else lsize = 0;
	if(k - 1 == lsize)return o -> v;
	else if(k <= lsize)return Find_kth(o -> ch[0],k);
	else return Find_kth(o -> ch[1], k - lsize - 1);
}
void Delete(node* &o, int x){
	if(o == NULL) return;
	int d = o -> cmp(x);
	if(d == -1){
		node* u = o;
		if(o -> ch[0] != NULL && o -> ch[1] != NULL){
			int d2 = (o -> ch[0] -> pri < o -> ch[1] -> pri) ? 0 : 1;
			rotate(o,d2);
			Delete(o -> ch[d2],x);
		}
		else {
			if(o -> ch[0]) o = o -> ch[0];
			else o = o -> ch[1];
			delete u;
		}
	}
	else Delete(o -> ch[d],x);
	if(o != NULL) o -> maintain();
}
void Insert(node* &o,int x){
	if(o == NULL) o = new node(x);
	else {
		//int d = (x <  o -> v ? 0 : 1);//不能用cmp函数，因为x有可能相同 相同就在右子树
		int d = o -> cmp(x);
		if(d == -1)return ; 
		Insert(o -> ch[d],x); 
		if(o -> ch[d] -> pri > o -> pri) rotate(o, d ^ 1);
	}
	o -> maintain();
}
int main()
{
	srand(time(NULL));
	while(~scanf("%d",&n)){
		node *root = NULL;
		getchar();
		char ch;
		int x;
		for(int i = 1; i <= n; ++i){
			scanf("%c%d",&ch,&x);
			getchar();
			if(ch == 'I'){
				Insert(root,x);
			}
			else if(ch == 'D'){
				Delete(root,x);
			}
			else if(ch == 'K'){
				int f = Find_kth(root,x);
				if(f == -1)printf("invalid\n");
				else printf("%d\n",f);
			}
			else {
				printf("%d\n",Count(root,x));
			}
		}
	}
	return 0;
}
