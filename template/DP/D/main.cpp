#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int mod=1000000007;
int T,m,n;
char S[17];
char DNA[4]={'A','T','C','G'};
int nxt[(1<<15)+100][4];
void add(long long& x,int b)
{
    x+=b;
    if(x>=mod) x-=mod;
}void add(long long& x,long long b)
{
    x+=b;
    if(x>=mod) x-=mod;
}
int dp[20],dp1[20];
long long res[2][(1<<15)+100];
long long ans[20];
/*
void print(int x)
{
    while(x)
    {
        if(x&1) printf("1");
        else printf("0");
        x>>=1;
    }
    printf(" ");
}*/
int main()
{
    //freopen("data.in","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        memset(res,0,sizeof(res));
        memset(ans,0,sizeof(ans));
        memset(nxt,0,sizeof(nxt));
       scanf("%s%d",S,&m);
       n=strlen(S);
       for(int i=0;i<1<<n;i++)
       {
           dp[0]=0;
           for(int j=0;j<n;j++)
           {
               if(i>>j&1) dp[j+1]=dp[j]+1;
               else dp[j+1]=dp[j];
           }
           for(int k=0;k<4;k++)
           {
               dp1[0]=0;
               for(int j=0;j<n;j++)
               {
                   if(S[j]==DNA[k])
                    dp1[j+1]=dp[j]+1;
                   else
                    dp1[j+1]=max(dp1[j],dp[j+1]);
               }
               int news=0;
               for(int j=n-1;j>=0;j--)
               {
                   if(dp1[j+1]-dp1[j])
                    news|=1<<j;
               }
               nxt[i][k]=news;
           }
       }
       /*
       for(int i=0;i<1<<n;i++)
       {
           printf("%d ",i);
           print(i);
           printf("\n");
            for(int j=0;j<4;j++)
                print(nxt[i][j]);
            printf("\n");

       }*/
       int now=0;
       res[now][0]=1;
       for(int i=0;i<m;i++)
       {
           now^=1;
           memset(res[now],0,sizeof(res[now]));
           for(int s=0;s<1<<n;s++)
           {
               for(int t=0;t<4;t++)
                add(res[now][nxt[s][t]],res[now^1][s]);
           }
       }
       for(int s=0;s<1<<n;s++)
       {
           int cnt=0,t=s;
           while(t)
           {
               if(t&1) cnt++;
               t>>=1;
           }
           add(ans[cnt],res[now][s]);
       }
       for(int i=0;i<=n;i++)
        printf("%I64d\n",ans[i]);
    }
    return 0;
}
