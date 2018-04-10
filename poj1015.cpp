#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;

int dp[30][1000];
int path[30][1000];
int p[300];
int d[300];
int ans[30];
int n, m;
int maxm;

int main()
{
    int tot = 1;
    while(scanf("%d %d",&n,&m) && m && n)
    {
        for(int i = 1; i <= n; i++)
        scanf("%d%d", &p[i], &d[i]);
        memset(dp, -1 ,sizeof(dp));
        memset(path, 0 ,sizeof(path));
        maxm=m * 20;
        dp[0][maxm] = 0;
         for(int j = 0; j < m; j++)
        {
            for(int k = 0; k <= maxm * 2; k++)
			if(dp[j][k] >= 0)
               {
                   for(int i = 1; i <= n; i++)
                       if(dp[j][k] + p[i] + d[i] > dp[j + 1][k + p[i] - d[i]])
                       {
                          int t1 = j;int t2 = k;
                           while(t1 > 0 && path[t1][t2] != i)
                           {
                               t2 -= p[path[t1][t2]]-d[path[t1][t2]];
                               t1--;
                           }
                           if(t1 == 0)
                           {
                               dp[j + 1][k + p[i] - d[i]] = dp[j][k] + p[i] + d[i];
                               path[j + 1][k + p[i] - d[i]] = i;
                           }         
                       }    
               }    
        }   
        int i = maxm;
        int j = 0;
        int k;
        while(dp[m][i + j] < 0 && dp[m][i - j] < 0)  j++;
        if(dp[m][i + j] > dp[m][i - j])  k = i + j;
        else k = i - j;
        printf("Jury #%d\n",tot++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n",(k-maxm+dp[m][k])/2,(dp[m][k]-k+maxm)/2);
        for(i = 1;i <= m; i++)
        {
            ans[i] = path[m - i + 1][k]; 
            k -= p[ans[i]] - d[ans[i]];
        }
        sort(ans + 1, ans + m + 1);
        for(i = 1; i <= m; i++)  
          printf(" %d",ans[i]);
        printf("\n\n");     
        
    }  
    return 0;   
}   
