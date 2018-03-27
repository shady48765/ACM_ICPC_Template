#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
const int mod=20101009;
const int maxn=10000005;
int notprime[maxn+10],prime[maxn+10],tot;
LL mu[maxn+10];
void seive()
{
    mu[1]=1;tot=0;
    for(LL i=2;i<maxn;i++)
    {
        if(!notprime[i])
        {
            prime[tot++]=i;
            mu[i]=-1;
        }
        for(int j=0;j<tot;j++)
        {
            if(prime[j]*i>maxn) break;
            notprime[prime[j]*i]=1;
            mu[prime[j]*i]=-mu[i];
            if(i%prime[j]==0)
            {
                mu[i*prime[j]]=0;
                break;
            }
        }
    }
    //for(int i=1;i<maxn;i++) mu[i]=(mu[i-1]+(LL)i%mod*i*mu[i]%mod)%mod;
    for(int i=1;i<maxn;i++) mu[i]=((LL)mu[i]*i%mod*i%mod+mu[i-1])%mod;
}
inline int sum(int n,int m)
{
    return ((LL)n*(n+1)/2%mod)*((LL)m*(m+1)/2%mod)%mod;
}
inline int solve(int n,int m)
{
    if(n>m) swap(n,m);
    int res=0;
    for(int i=1,last=0;i<=n;i=last+1)
    {
        last=min(n/(n/i),m/(m/i));
        res=(res+(LL)(mu[last]-mu[i-1])*sum(n/i,m/i)%mod)%mod;
    }
    return res;
}
int answer(int n,int m)
{
    if(n>m) swap(n,m);
    int res=0;
    for(int i=1,last=0;i<=n;i=last+1)
    {
        last=min(n/(n/i),m/(m/i));
        res=(res+(LL)(i+last)*(last-i+1)/2%mod*solve(n/i,m/i)%mod)%mod;
    }
    return res;
}
int main()
{
    seive();
    int n,m;
    scanf("%d%d",&n,&m);
    printf("%d",(answer(n,m)+mod)%mod);
    return 0;
}
