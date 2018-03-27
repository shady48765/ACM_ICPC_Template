#include <iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
typedef long long ll;
const int mod=1000000993;
const int N=11111111;
int cnt,prime[N+10],vis[N+10];
void seive()
{
    cnt=0;
    prime[cnt++]=1;
    for(int i=2;i<=N;i++){
        if(!vis[i]){
            prime[cnt++]=i;
        }
        for(int j=1;j<cnt;j++){
            if(1LL*prime[j]*i>N) break;
            vis[prime[j]*i]=1;
            if(i%prime[j]==0) break;
        }
    }
}
ll fpow(ll a,int n)
{
    ll res=1;
    while(n){
        if(n&1){
            res=(res*a)%mod;
        }
        a=(a*a)%mod;
        n>>=1;
    }
    return res;
}
ll inv(ll a)
{
    return fpow(a,mod-2);
}
const int MaxP=750000;//733409;
ll val[MaxP<<2],tag[MaxP<<2];
void pushup(int o)
{
    val[o]=(val[o<<1]+val[o<<1|1])%mod;
}
void pushdown(int o)
{
    if(tag[o]!=1){
        tag[o<<1]=tag[o<<1]*tag[o]%mod;
        tag[o<<1|1]=tag[o<<1|1]*tag[o]%mod;
        val[o<<1]=val[o<<1]*tag[o]%mod;
        val[o<<1|1]=val[o<<1|1]*tag[o]%mod;
        tag[o]=1;
    }
}
void build(int o,int l,int r)
{
    if(l==r)
    {
        val[o]=prime[l+1]-prime[l];
        tag[o]=1;
    }
    else
    {
        int mid=(l+r)>>1;
        tag[o]=1;
        build(o<<1,l,mid);
        build(o<<1|1,mid+1,r);
        pushup(o);
    }
}
void update(int o,int l,int r,int L,int R,ll v)
{
    if(L<=l&&r<=R)
    {
        val[o]=(val[o]*v)%mod;
        tag[o]=(tag[o]*v)%mod;
    }
    else
    {
        pushdown(o);
        int mid=(l+r)>>1;
        if(L<=mid)
            update(o<<1,l,mid,L,R,v);
        if(R>mid)
            update(o<<1|1,mid+1,r,L,R,v);
        pushup(o);
    }
}
int main()
{
    freopen("answer.txt","w",stdout);
    seive();
    prime[cnt]=N+1;
    build(1,0,cnt-1);
    ll res=val[1];
    for(int r=0;r<N;r++)
    {
        int x;x=N-r;
        for(int i=2;i*i<=x;i++){
            if(x%i) continue;
            int ct=0;
            while(x%i==0){
                ++ct;x/=i;
            }
            int idx=lower_bound(prime,prime+cnt,i)-prime;
            update(1,0,cnt-1,idx,cnt-1,fpow(i,ct));
        }
        if(x>1){
            int idx=lower_bound(prime,prime+cnt,x)-prime;
            update(1,0,cnt-1,idx,cnt-1,x);
        }
        x=r+1;
        for(int i=2;i*i<=x;i++){
            if(x%i) continue;
            int ct=0;
            while(x%i==0){
                ++ct;x/=i;
            }
            int idx=lower_bound(prime,prime+cnt,i)-prime;
            update(1,0,cnt-1,idx,cnt-1,inv(fpow(i,ct)));
        }
        if(x>1){
            int idx=lower_bound(prime,prime+cnt,x)-prime;
            update(1,0,cnt-1,idx,cnt-1,inv(x));
        }
        res=(res+val[1])%mod;
    }
    cout<<res<<endl;
    return 0;
}
