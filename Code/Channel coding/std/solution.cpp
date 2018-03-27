#include <iostream>
#include<cstring>
#include<cstdio>
using namespace std;
const int mod=1e9+7;
int T,n,m,d,now;
int dp[2][1<<15][16];
int c[20][20];
char maz[54][15];
int one[54][16],zero[54][16];
void init()
{
    memset(c,0,sizeof(c));
    c[0][0]=1;
    for(int i=1;i<=15;i++)
        for(int j=0;j<=15;j++)
            c[i][j]=j?c[i-1][j-1]+c[i-1][j]:1;
}
void add(int& x,int y)
{
    x+=y;
    if(x>=mod)
        x-=mod;
}
//brute force
int DP[2][1<<15];

int countbit(int x)
{
    int cnt=0;
    while(x)
    {
        cnt++;
        x-=(x&-x);
    }
    return cnt;
}
long long pow(int base,int n)
{
    long long res=1;
    long long b=base;
    while(n)
    {
        if(n&1)
        {
            res*=b;
            res%=mod;
        }
        b*=b;
        b%=mod;
        n>>=1;
    }
    return res%mod;
}
void calc()
{
    memset(DP,0,sizeof(DP));
    int now=0;
    for(int s=0;s<(1<<m);s++) DP[now][s]=1;
    for(int i=1;i<n;i++)
    {
        now^=1;memset(DP[now],0,sizeof(DP[now]));
        for(int sp=0;sp<(1<<m);sp++)
            for(int s=0;s<(1<<m);s++)
                if(countbit(s^sp)<=d)
            {
                add(DP[now][s],DP[now^1][sp]);
            }
    }
    int res=0;
    for(int s=0;s<(1<<m);s++)
        add(res,DP[now][s]);
    cout<<"brute force"<<endl;
    cout<<res<<endl;
}
char a[]="24.out";
char b[]="24.res";
int main()
{
    //init();
    freopen(a,"r",stdin);
    freopen(b,"w",stdout);
    scanf("%d%d%d",&n,&m,&d);
    memset(one,0,sizeof(one));
    memset(zero,0,sizeof(zero));
    for(int i=0;i<n;i++)
    {
        scanf("%s",maz[i]);
        for(int j=0;j<m;j++) if(maz[i][j]=='1') one[i][j]=1;
        for(int j=0;j<m;j++) if(maz[i][j]=='0') zero[i][j]=1;
    }
    memset(dp,0,sizeof(dp));
    now=0;
    for(int s=0;s<(1<<m);s++)
    {
        bool ok=true;
        for(int i=0;i<m;i++) if(one[0][i]&&((s>>i&1)==0)) ok=false;
        for(int i=0;i<m;i++) if(zero[0][i]&&(s>>i&1)) ok=false;
        if(ok)
        dp[now][s][0]=1;
    }
    for(int i=1;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            now^=1;
            memset(dp[now],0,sizeof(dp[now]));
            for(int t=0;t<=d;t++)
            for(int s=0;s<(1<<m);s++)
            {
                if(zero[i][j])
                {
                    int ns=s^(1<<j);
                    if((ns>>j&1)==0)
                        add(dp[now][s^(1<<j)][t+1],dp[now^1][s][t]);
                    if((s>>j&1)==0)
                        add(dp[now][s][t],dp[now^1][s][t]);
                }
                else if(one[i][j])
                {
                    int ns=s^(1<<j);
                    if((ns>>j&1)==1)
                        add(dp[now][s^(1<<j)][t+1],dp[now^1][s][t]);
                    if((s>>j&1)==1)
                        add(dp[now][s][t],dp[now^1][s][t]);
                }
                else
                {
                    add(dp[now][s^(1<<j)][t+1],dp[now^1][s][t]);
                    add(dp[now][s][t],dp[now^1][s][t]);
                }
            }
        }
        for(int s=0;s<(1<<m);s++) for(int t=1;t<=d;t++)
        {
            add(dp[now][s][0],dp[now][s][t]);
            dp[now][s][t]=0;
        }
    }
    int res=0;
    for(int s=0;s<(1<<m);s++)
        for(int t=0;t<=d;t++) add(res,dp[now][s][t]);
    printf("%d\n",res);
    //int tp=0;
    //for(int i=0;i<=d;i++) add(tp,c[m][i]);
    //cout<<pow(2,m)%mod*pow(tp,n-1)%mod<<endl;
    //calc();
    return 0;
}
