#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int dp[10][90][90][90];//dp[i][sum][mod][res]
int ten[10];
void pre()
{
    memset(dp,0,sizeof(dp));
    ten[1]=1;for(int i=2;i<=9;i++) ten[i]=ten[i-1]*10;
    for(int i=1;i<=81;i++) dp[0][0][i][0]=1;
    for(int i=1;i<=9;i++)
        for(int s=0;s<=81;s++)
            for(int mod=1;mod<=81;mod++)
                for(int res=0;res<mod;res++)
                    for(int t=0;t<10;t++)
                        if(dp[i-1][s][mod][res])
                            dp[i][s+t][mod][(t+res*10)%mod]+=dp[i-1][s][mod][res];
}
int f(int x)
{
    int re=0,n(x);
    while(x)
    {
        re+=x%10;
        x/=10;
    }
    return n%re==0;
}
int calc(int x)
{
    if(!x) return 0;
    int A[12],len=0;
    int sum=0,res=0,re=0;
    if(f(x)) ++res;
    while(x)
    {
        ++len;
        A[len]=x%10;x/=10;
    }
    A[len+1]=0;
    for(int i=len;i>=1;i--)
    {
        sum+=A[i+1];
        re+=A[i+1]*ten[i+1];
        for(int j=0;j<A[i];j++)
        {
            for(int s=sum+j;s<=81;s++)
            {
                if(s==0) continue;
                res+=dp[i-1][s-sum-j][s][(s-(j*ten[i]+re)%s)%s];
            }
        }
    }
    return res;
}
int main()
{
    pre();
    int T,l,r;
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        scanf("%d%d",&l,&r);
        printf("Case %d: %d\n",kase,calc(r)-calc(l-1));
    }
    return 0;
}
