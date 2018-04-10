#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#define MAXN 200005
using namespace std;

int n, m = 128;
char s[MAXN];
int rank[MAXN], sa[MAXN], hei[MAXN];
int w[MAXN], t[MAXN], t2[MAXN];

void cal(){
	int *x = t, *y = t2;
	for(int i = 0; i < m; ++i) w[i] = 0;
	for(int i = 0; i < n; ++i) w[x[i] = s[i]]++;
	for(int i = 1; i < m; ++i) w[i] += w[i - 1];
	for(int i = n - 1; i >= 0; --i) sa[--w[x[i]]] = i;
	for(int k = 1; k <= n; k <<= 1){
		int p = 0;
		for(int i = n - k; i < n; ++i) y[p++] = i;
		for(int i = 0; i < n; ++i) if(sa[i] >= k) y[p++] = sa[i] - k;
		for(int i = 0; i < m; ++i) w[i] = 0;
		for(int i = 0; i < n; ++i) w[x[y[i]]]++;
		for(int i = 1; i < m; ++i) w[i] += w[i - 1];
		for(int i = n - 1; i >= 0; --i) sa[--w[x[y[i]]]] = y[i];
		swap(x, y);
		p = 1; x[sa[0]] = 0;
		for(int i = 1; i < n; ++i)
		x[sa[i]] = y[sa[i - 1]] == y[sa[i]] && y[sa[i - 1] + k] == y[sa[i] + k] ? p - 1 : p++;
		if(p >= n)break;
		m = p;
	}
}

void getheight(){
	int k = 0;
	for(int i = 1; i <= n; ++i)rank[sa[i]] = i;
	for(int i = 0; i < n; ++i){
		if(k) k--;
		int j = sa[rank[i] - 1];
		while(s[i + k] == s[j + k])
		k++;
		hei[rank[i]] = k;
	}
}
int main()
{
	//freopen("poj2774.in", "r", stdin);
	//freopen("poj2774.out", "w", stdout);
		gets(s);
		int j = strlen(s);
		s[j] = '$';
		gets(s + j + 1);
		n = strlen(s);
		//for(int i = 0; i < n; ++i)r[i] = s[i];
		cal();
		getheight();
		int ans = 0;
		/*for(int i = 1; i <= n; ++i){
			if(hei[i] <= ans)continue;
			if((j <= sa[i] && j > sa[i - 1]) || (j > sa[i] && j <= sa[i - 1])) ans = hei[i];
		}*/
		for(int i=1;i<n;i++)
		{
			if((sa[i-1]<j&&sa[i]>=j)||(sa[i-1]>=j&&sa[i]<j))
				ans=max(ans,hei[i]);
		}
		printf("%d\n", ans);
	
	return 0;
}
