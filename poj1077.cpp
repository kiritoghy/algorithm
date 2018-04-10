#include<cstdio>
#include<iostream>
#include<string>
#include<algorithm>
#include<queue>
#include<cstring>
using namespace std;

const int MAX=1000000;
int sr[9],po;
int fan[9]={1,1,2,6,24,120,720,5040,40320};
bool visit[MAX];
char path[MAX];
int pre[MAX];
struct lmx{
    int a[9];
    int pos;
};
lmx s,t,h;
int temp = 0;
int dir[4][2]={{-1,0},{1,0},{0,-1},{0,1}};
char st[5]="durl";
int str;

int kgto(int *m,int n)
{
    int i,j,num,s=0;
    for(i=0;i<n-1;i++)
    {
        num=0;
        for(j=i+1;j<n;j++)
        {
            if(m[j]<m[i]) num++;
        }
        s+=num*fan[8-i];
    }
    return s;
}
int bfs()
{
    memset(visit,false,sizeof(visit));
    int i,val,x,y,xx,yy;
    queue<lmx>q;
    for(i=0;i<8;i++)//µ¹×ÅËÑ·½±ãÊä³ö 
    {
        s.a[i]=i+1;
    }
    s.a[8]=0;
    s.pos=8;
    q.push(s);
    val=kgto(s.a,9);
    str = val;
    visit[val]=true;
    while(!q.empty())
    {
        h=q.front();
        q.pop();
        x=h.pos/3;
        y=h.pos%3;
        int id = kgto(h.a,9);
        for(i=0;i<4;i++)
        {
            xx=x+dir[i][0];
            yy=y+dir[i][1];
            if(xx>=0&&xx<3&&yy>=0&&yy<3)
            {
                t=h;
                swap(t.a[h.pos],t.a[xx*3+yy]);
                t.pos=3*xx+yy;
                val=kgto(t.a,9);
                if(visit[val]==false)
                {
                    visit[val]=true;
                    pre[val] = id;
                    path[val] = st[i];
                    q.push(t);
                    if(val == temp)return 1;
                }
            }
        }
    }
}
int main()
{
    char ch[105];
    int i;
    
    while(gets(ch))
    {
    	int count = 0;
    	for(int i = 0; i < strlen(ch); ++i){
    		if(ch[i] >= '0' && ch[i] <= '9')sr[count] = ch[i] - '0',po = count++;
    		else if(ch[i] == 'x')sr[count] = 0,po = count++;
    	}
        temp=kgto(sr,9);
        bfs();
        if(visit[temp]==false) puts("unsolvable");
        else{
        	int id = temp;
        	while(id != str){
        		printf("%c",path[id]);
        		id = pre[id];
        	}
        }
    }
    return 0;
}
