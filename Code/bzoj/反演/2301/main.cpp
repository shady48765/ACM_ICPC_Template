#include <cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
const int maxn=50010;
int mu[maxn],sum[maxn],not_prime[maxn];
int prime[10010],tot;
void sieve()
{
    mu[1]=1;tot=0;
    memset(not_prime,0,sizeof(not_prime));
    for(int i=2;i<=maxn;i++)
    {
        if(!not_prime[i])
        {
            prime[tot++]=i;
            mu[i]=-1;
        }
        for(int j=0;j<tot;j++)
        {
            if(prime[j]*i>maxn) break;
            not_prime[prime[j]*i]=1;
            mu[prime[j]*i]=-mu[i];
            if(i%prime[j]==0){
                mu[i*prime[j]]=0;break;
            }
        }
    }
}
long long solve(int n,int m)
{
    if(n>m) swap(n,m);
    long long res=0;
    for(int i=1,last=0;i<=n;i=last+1)
    {
        last=min(n/(n/i),m/(m/i));
        res+=(long long)(sum[last]-sum[i-1])*(m/i)*(n/i);
    }
    return res;
}
int main()
{
    sieve();
    for(int i=1;i<=maxn;i++) sum[i]=sum[i-1]+mu[i];
    int a,b,c,d,k,q;
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);
        long long ans=solve(b/k,d/k)-solve(b/k,(c-1)/k)-solve((a-1)/k,d/k)+solve((a-1)/k,(c-1)/k);
        printf("%lld\n",ans);
    }
    return 0;
}
