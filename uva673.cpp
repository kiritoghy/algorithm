#include<cstdio>
#include<iostream>
#include<stack>
#include<cstring>
using namespace std;

int T;
char s[2000];

int main()
{
	scanf("%d", &T);
	scanf(" ");
	while(T--){
		stack<char>q;
		gets(s);
		int len = strlen(s);
		for(int i = 0; i < len; ++i){
			if(q.empty() && (s[i] == ')' || s[i] == ']') && s[i] != '\n'){
				q.push(s[i]);
				break;
			}
			if(s[i] == '(' || s[i] == '[')q.push(s[i]);
			if(s[i] == ']' && q.top() == '[')q.pop();
			if(s[i] == ')' && q.top() == '(')q.pop();
		}
		if(q.empty())printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}
