#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
int gcd(int x,int y)
{
    return y?gcd(y,x%y):x;
}
long long dp[22][3000][55];
int id[3000];
int ten[25];
int lcm(int x,int y)
{
    if(!x) return y;
    if(!y) return x;
    return x*y/gcd(x,y);
}
const int mod=2520;
int G[50]={0,1,2,3,4,5,6,7,8,9,10,12,14,15,18,20,21,24,28,30,35,36,40,42,45,56,60,63,70,72,84,90,105,120,126,140,168,180,210,252,280,315,360,420,504,630,840,1260,2520};
void add(int &a,int b)
{
    a+=b;
    if(a>=mod)
        a-=mod;
}
int mylcm[3000][3000];
void pre()
{
    ten[1]=1;
    for(int i=2;i<=22;i++) ten[i]=ten[i-1]*10%mod;
    for(int i=1;i<=48;i++) id[G[i]]=i;
    for(int i=0;i<=mod;i++)
        for(int j=i;j<=mod;j++)
            mylcm[i][j]=mylcm[j][i]=lcm(i,j);
    dp[0][0][1]=1;
    for(int i=1;i<=19;i++)
        for(int j=0;j<mod;j++)
            for(int t=1;t<=48;t++)
                for(int k=0;k<10;k++)
                    dp[i][(j*10+k)%mod][id[mylcm[k][G[t]]]]+=dp[i-1][j][t];
}
int f(long long x)
{
    long long n(x);
    int y;
    while(x)
    {
        y=x%10;
        x/=10;
        if(y==0) continue;
        if(n%y) return 0;
    }
    return 1;
}
long long calc(long long x)
{
    if(!x) return 1;
    long long ans=0;
    int LCM=1,sm=0;
    int A[23],len=0;
    if(f(x)) ans++;
    while(x)
    {
        ++len;
        A[len]=x%10;
        x/=10;
    }
    A[len+1]=0;
    for(int i=len;i>=1;i--)
    {
        LCM=mylcm[LCM][A[i+1]];
        sm=(sm+A[i+1]*ten[i+1])%mod;
        for(int j=0;j<A[i];j++)
        {
            int tlcm=mylcm[LCM][j];
            int tsm=(sm+j*ten[i])%mod;
            for(int res=0;res<mod;res++)
                for(int k=1;k<=48;k++)
                    if(res%mylcm[tlcm][G[k]]==0)
                        ans+=dp[i-1][(mod-tsm+res)%mod][k];
        }
    }
    return ans;
}
int main()
{
    //freopen("data.out","r",stdin);
    pre();
    int T;
    long long l,r;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%I64d%I64d",&l,&r);
        printf("%I64d\n",calc(r)-calc(l-1));
    }
    return 0;
}
