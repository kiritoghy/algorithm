#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <vector>
#define SIZE 26
#define idx(a) ((a) - 'A')
using namespace std;

int vis[1000 + 5];
bool yes = 0;
int n, tcnt, scnt, m;
char ss[2000000 + 5];
struct node {
	node *fail, *back;
	node *ch[SIZE];
	int v;
	void init(){
		for(int i = 0; i < SIZE; ++i)ch[i] = NULL;
		fail = back = NULL;
		v = 0;
	}
}T[1000 * 50 + 10], *root;

inline node *newnode() {
	T[tcnt].init();
	return &T[tcnt++];
}
inline void insert(char *s, int vv) {
	int l = strlen(s);
	node *u = root;
	
	for(int i = 0; i < l; ++i){
		int c = idx(s[i]);
		
		if(u -> ch[c] == NULL)u -> ch[c] = newnode();
		u = u -> ch[c];
	}
	u -> v = vv;
}
inline void Build_AC(){
	queue<node *>q;
	q.push(root);
	//root -> fail = root -> back = root;
	while(!q.empty()){
		node *u = q.front(); q.pop();
		
		for(int c = 0; c < SIZE; ++c){
			node *v = u -> ch[c];
			
			if(v != NULL){
				if(u == root) v -> fail = v -> back = root;
				else {
					node *tmp = u -> fail;
					
					while(tmp != root && tmp -> ch[c] == NULL)tmp = tmp -> fail;
					v -> fail = tmp -> ch[c];
					
					if(v -> fail == NULL) v -> fail = root;
					v -> back = v -> fail -> v ? v -> fail : v -> fail -> back;
				}
				q.push(v);
			}
		}
		
	}
}
inline void print(node *u){
	if(u == NULL)return ;
	if(u -> v) vis[u -> v]++;
	print(u -> back);
}
void Query(char *s){
	int l = strlen(s);
	node *u = root;
	for(int i = 0; i < l; ++i){
		if(s[i] < 'A' || s[i] > 'Z'){
			u = root;
			continue;
		}
		int c = idx(s[i]);
		
		while(u != root && u -> ch[c] == NULL) u = u -> fail;
		u = u -> ch[c];
		
		if(u == NULL) u = root;
		if(u -> v)print(u);
		else print(u -> back);
	}
}
int main()
{
	while(~scanf("%d", &n)){
		scnt = 0;
		tcnt = 0;
		root = newnode();
		char s[1000 + 5][200 + 5];
		for(int i = 1; i <= n; ++i){
			scanf("%s", s[++scnt]);
			insert(s[scnt], scnt);
		}
		
		Build_AC();
		scanf("%s", ss);
		Query(ss);
		for(int i = 1; i <= scnt; ++i){
			if(vis[i]){
				printf("%s: %d\n", s[i], vis[i]);
				vis[i] = 0;
			}
		}
	}
	
	
	return 0;
}
