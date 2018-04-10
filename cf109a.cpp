#include<cstdio>
#include<iostream>
using namespace std;

int n;

int main()
{
	while(~scanf("%d",&n)){
		int c4 = 0,c7 = 0;
		for(int i = n / 7; i >= 0; --i){
			if((n - (i * 7)) % 4 == 0){
				c7 = i;
				c4 = (n - (i * 7)) / 4;
				break;
			}
		}
		if(!c4 && !c7){
			printf("-1\n");
		}
		for(int i = 1; i <= c4; ++i)
		printf("4");
		for(int i = 1; i <= c7; ++i)
		printf("7");
		printf("\n");
	}
	return 0;
}
