#include <cstdio>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>

using namespace std;
const int maxn=200010;
int A[maxn],add[maxn<<2],add2[maxn<<2],mi[maxn<<2],mx[maxn<<2],mintag[maxn<<2],maxtag[maxn<<2];
void pushup(int o)
{
    mi[o]=min(mi[o<<1],mi[o<<1|1]);
    mx[o]=max(mx[o<<1],mx[o<<1|1]);
    maxtag[o]=-1;
}
void pushdown_min(int o)
{
    mx[o<<1]=min(mx[o<<1],mintag[o]);
    mx[o<<1|1]=min(mx[o<<1],mintag[o]);
    mintag[o]=-1;
}
void pushdown_max(int o)
{
    mi[o<<1]=max(mi[o<<1],maxtag[o]);
    mi[o<<1|1]=max(mi[o<<1|1],maxtag[o]);
}
void pushdown(int o)
{
    if(add[o]!=0)
    {
        add2[o]+=add[o];
        if(mintag[o]!=-1)
            mintag[o]-=add[o];
        if(maxtag[o]!=-1)
            maxtag[o]-=add[o];
        add[o]=0;
    }
    if(mintag[o]!=-1)
    {
        pushdown_min(o);
    }
    if(maxtag[o]!=-1)
    {
        pushdown_max(o);
    }
    if(add2[])

}
void build(int o,int l,int r)
{
    if(l==r)
    {
        mi[o]=mx[o]=A[l];
        mintag[o]=maxtag[o]=-1;
        add[o]=add2[o]=0;
    }
    else
    {
        int mid=(l+r)>>1;
        build(o<<1,l,mid);
        build(o<<1|1,mid+1,r);
        pushup(o);
    }
}

void update_add(int o,int l,int r,int L,int R)
{
    //if(L<)
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&A[i]);
    }

    return 0;
}
