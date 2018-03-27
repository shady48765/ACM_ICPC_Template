#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
const int maxn=100110;
const int mod=1000000007;
int n;
struct num
{
    int a,b;
    bool operator<(const num& rhs) const
    {
        return a<rhs.a;
    }
}N[maxn];
int C[maxn],tot;
LL fpow(LL base,int pow)
{
    LL res=1;
    while(pow)
    {
        if(pow&1)
            res*=base,res%=mod;
        base*=base;
        base%=mod;
        pow>>=1;
    }
    return res;
}
LL tag[maxn<<2],sum[maxn<<2];
int cnt[maxn<<2];
void pushdown(int o)
{
    if(tag[o])
    {
        sum[o<<1]=sum[o<<1]*fpow(2,tag[o])%mod;
        sum[o<<1|1]=sum[o<<1|1]*fpow(2,tag[o])%mod;
        tag[o<<1]+=tag[o];
        tag[o<<1|1]+=tag[o];
        tag[o]=0;
    }
}
void pushup(int o)
{
    sum[o]=sum[o<<1]+sum[o<<1|1];
    sum[o]%=mod;
    cnt[o]=cnt[o<<1]+cnt[o<<1|1];
}
int query_cnt(int o,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)
        return cnt[o];
    else
    {
        pushdown(o);
        int mid=(l+r)>>1;
        int res=0;
        if(L<=mid)
            res+=query_cnt(o<<1,l,mid,L,R);
        if(R>mid)
            res+=query_cnt(o<<1|1,mid+1,r,L,R);
        pushup(o);
        return res;
    }
}
void update_cnt(int o,int l,int r,int p)
{
    if(l==r)
        cnt[o]++;
    else
    {
        pushdown(o);
        int mid=(l+r)>>1;
        if(p<=mid)
            update_cnt(o<<1,l,mid,p);
        if(p>mid)
            update_cnt(o<<1|1,mid+1,r,p);
        pushup(o);
    }
}
void update(int o,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)
    {
        tag[o]++;
        sum[o]=sum[o]*2%mod;
    }
    else
    {
        pushdown(o);
        int mid=(l+r)>>1;
        if(L<=mid)
            update(o<<1,l,mid,L,R);
        if(R>mid)
            update(o<<1|1,mid+1,r,L,R);
        pushup(o);
    }
}
void update(int o,int l,int r,int p,LL val)
{
    if(l==r)
    {
        sum[o]+=val;
        sum[o]%=mod;
    }
    else
    {
        pushdown(o);
        int mid=(l+r)>>1;
        if(p<=mid)
            update(o<<1,l,mid,p,val);
        if(p>mid)
            update(o<<1|1,mid+1,r,p,val);
        pushup(o);
    }
}
LL query_sum(int o,int l,int r,int L,int R)
{
    if(L<=l&&r<=R)
    {
        return sum[o];
    }
    else
    {
        pushdown(o);
        int mid=(l+r)>>1;
        LL res=0;
        if(L<=mid)
            res+=query_sum(o<<1,l,mid,L,R);
        if(R>mid)
            res+=query_sum(o<<1|1,mid+1,r,L,R);
        res%=mod;
        pushup(o);
        return res;
    }
}
int main()
{
    //freopen("data.in","r",stdin);
    while(scanf("%d",&n)!=EOF)
    {
        tot=0;
        for(int i=0;i<n;i++)
            scanf("%d%d",&N[i].a,&N[i].b),C[tot++]=N[i].b;
        sort(N,N+n);
        sort(C,C+tot);
        tot=unique(C,C+tot)-C;
        memset(tag,0,sizeof(tag));
        memset(sum,0,sizeof(sum));
        memset(cnt,0,sizeof(cnt));
        LL ans=0,tp;
        for(int i=0;i<n;i++)
        {
            int x=lower_bound(C,C+tot,N[i].b)-C;
            tp=fpow(2,query_cnt(1,0,tot,0,x))*fpow(3,N[i].b)%mod;
            ans+=query_sum(1,0,tot,x+1,tot)*fpow(2,N[i].a)%mod;
            ans+=tp*fpow(2,N[i].a)%mod;
            ans%=mod;
            update(1,0,tot,x+1,tot);
            update(1,0,tot,x,tp);
            update_cnt(1,0,tot,x);
            /*
            tp=fpow(2,N[i].a)*fpow(3,N[i].b)%mod;
            int ct=0;
            if(x-1!=-1)
            {
                ct=query_cnt(1,0,tot,0,x-1);
            }*/
        }
        printf("%I64d\n",ans);
    }
    return 0;
}
