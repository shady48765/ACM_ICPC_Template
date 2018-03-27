#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#define inf 2000000000
#define maxn 200020

using namespace std;

int a[maxn];
int mx[maxn*3],mi[maxn*3],ad[maxn*3],high[maxn*3],low[maxn*3];
int ll,rr;

void cover(int x,int l,int r,int z)
{
    mi[x]=min(max(mi[x],high[x]),low[x])+z;
    mx[x]=max(min(mx[x],low[x]),high[x])+z;
}

void down(int x,int l,int r)
{
    int mid=(l+r)>>1;
    low[x*2]=min(low[x*2],low[x]-ad[x*2]);
    low[x*2+1]=min(low[x*2+1],low[x]-ad[x*2+1]);
    high[x*2]=max(high[x*2],high[x]-ad[x*2]);
    high[x*2+1]=max(high[x*2+1],high[x]-ad[x*2+1]);
    ad[x*2]+=ad[x];
    ad[x*2+1]+=ad[x];
    cover(x*2,l,mid,ad[x]);
    cover(x*2+1,mid+1,r,ad[x]);
    ad[x]=0;
    low[x]=inf;
    high[x]=0;
}

void add(int x,int l,int r,int z)
{
    if (ll<=l&&r<=rr)
    {
        ad[x]+=z;
        cover(x,l,r,z);
        return ;
    }
    down(x,l,r);
    int mid=(l+r)>>1;
    if (ll<=mid) add(x*2,l,mid,z);
    if (rr>mid) add(x*2+1,mid+1,r,z);
    mi[x]=min(mi[x*2],mi[x*2+1]);
    mx[x]=max(mx[x*2],mx[x*2+1]);
}

void cov_min(int x,int l,int r,int z)
{
    if (ll<=l&&r<=rr)
    {
        low[x]=min(low[x],z-ad[x]);
        cover(x,l,r,0);
        return ;
    }
    down(x,l,r);
    int mid=(l+r)>>1;
    if (ll<=mid) cov_min(x*2,l,mid,z);
    if (rr>mid) cov_min(x*2+1,mid+1,r,z);
    mi[x]=min(mi[x*2],mi[x*2+1]);
    mx[x]=max(mx[x*2],mx[x*2+1]);
}

void cov_max(int x,int l,int r,int z)
{
    if (ll<=l&&r<=rr)
    {
        high[x]=max(high[x],z-ad[x]);
        cover(x,l,r,0);
        return ;
    }
    down(x,l,r);
    int mid=(l+r)>>1;
    if (ll<=mid) cov_max(x*2,l,mid,z);
    if (rr>mid) cov_max(x*2+1,mid+1,r,z);
    mi[x]=min(mi[x*2],mi[x*2+1]);
    mx[x]=max(mx[x*2],mx[x*2+1]);
}

int ask_min(int x,int l,int r)
{
    int tmp=inf;
    if (ll<=l&&r<=rr) return mi[x];
    down(x,l,r);
    int mid=(l+r)>>1;
    if (ll<=mid) tmp=min(tmp,ask_min(x*2,l,mid));
    if (rr>mid) tmp=min(tmp,ask_min(x*2+1,mid+1,r));
    mi[x]=min(mi[x*2],mi[x*2+1]);
    mx[x]=max(mx[x*2],mx[x*2+1]);
    return tmp;
}

int ask_max(int x,int l,int r)
{
    int tmp=0;
    if (ll<=l&&r<=rr) return mx[x];
    down(x,l,r);
    int mid=(l+r)>>1;
    if (ll<=mid) tmp=max(tmp,ask_max(x*2,l,mid));
    if (rr>mid) tmp=max(tmp,ask_max(x*2+1,mid+1,r));
    mi[x]=min(mi[x*2],mi[x*2+1]);
    mx[x]=max(mx[x*2],mx[x*2+1]);
    return tmp;
}


int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=3*n;i++)
    {
        low[i]=inf;
        high[i]=0;
    }
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        ll=rr=i;
        add(1,1,n,a[i]);
    }
    int sign,x,y,z;
    for (int i=1;i<=m;i++)
    {
        scanf("%d",&sign);
        if (sign==1)
        {
           scanf("%d%d%d",&x,&y,&z);
           ll=x;rr=y;
           add(1,1,n,z);
        }
        if (sign==2)
        {
            scanf("%d%d%d",&x,&y,&z);
            ll=x; rr=y;
            cov_min(1,1,n,z);

        }
        if (sign==3)
        {
            scanf("%d%d%d",&x,&y,&z);
            ll=x; rr=y;
            cov_max(1,1,n,z);
        }
        if (sign==4)
        {
            scanf("%d%d",&x,&y);
            ll=x; rr=y;
            printf("%d %d\n",ask_min(1,1,n),ask_max(1,1,n));
        }
    }
    return 0;
}
