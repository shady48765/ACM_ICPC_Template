#include <iostream>
#include<cstring>
#include<cstdio>
using namespace std;
typedef long long ll;
const int mod=100000007;
const int n=1000000;
ll fact[1000010],pow2[1000010];
ll fpow(ll x,int n)
{
    ll res=1;
    while(n){
        if(n&1){
            res=res*x%mod;
        }
        x=x*x%mod;
        n>>=1;
    }
    return res;
}
ll iv(ll x)
{
    return fpow(x,mod-2);
}
ll C(int a,int b)
{
    ll res=1;
    res=res*fact[b]%mod;
    res=res*iv(fact[a])%mod;
    res=res*iv(fact[b-a])%mod;
    return res;
}
int main()
{
    freopen("answer.out","w",stdout);
    fact[0]=pow2[0]=1;
    for(int i=1;i<=1000000;i++)
    {
        fact[i]=fact[i-1]*i%mod;
        pow2[i]=pow2[i-1]*2%mod;
    }
    ll ans=0;
    for(int a=0;a<2;a++)
        for(int b=0;b<2;b++)
            for(int two=0;two<=n;two++)
        {
            int one=n-a-b-1-3*two;
            if(one&1) continue;
            if(one<0) continue;
            one/=2;
            int t=one+two+1;
            ans+=fact[t]*fact[two+a+b]%mod*pow2[two]%mod*fact[one+two]%mod*C(two,t-1)%mod;
            ans%=mod;
        }
    cout<<ans<<endl;
    return 0;
}
