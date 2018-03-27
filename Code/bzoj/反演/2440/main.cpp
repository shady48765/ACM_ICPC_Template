#include <cstdio>
#include<algorithm>
#include<iostream>
using namespace std;
typedef long long LL;
const int maxn=100000;
int prime[maxn+10],tot;
int isprime[maxn+10];
int mu[maxn+10];
void seive()
{
    mu[1]=1;tot=0;
    for(int i=2;i<=maxn;i++)
    {
        if(!isprime[i])
        {
            prime[tot++]=i;
            mu[i]=-1;
        }
        for(int j=0;j<tot;j++)
        {
            if(prime[j]*i>maxn) break;
            isprime[prime[j]*i]=1;
            mu[prime[j]*i]=-mu[i];
            if(i%prime[j]==0)
            {
                mu[i*prime[j]]=0;
                break;
            }
        }
    }
}
long long check(long long k)
{
    long long ans=0;
    for(long long i=1;i*i<=k;i++)
    {
        ans+=mu[i]*(k/(i*i));
    }
    return ans;
}
int main()
{
    seive();
    int T;
    long long k;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%lld",&k);
        long long l=1,r=2147483640,mid,res;
        while(l<r)
        {
            mid=(l+r)>>1;
            long long tp=check(mid);
            if(tp<k)
                l=mid+1;
            else if(tp>=k)
            {
                r=mid;
                if(tp==k) res=mid;
            }
        }
        printf("%lld\n",res);
    }
    return 0;
}
