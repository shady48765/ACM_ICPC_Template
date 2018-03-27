#include <cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#define MOD 1000003
using namespace std;
int n,m,cnt,root;
int A[1010],l[1010],r[1010],w[1010],siz[1010];
long long res=1;
long long fastpow(int x)
{
    long long nn=MOD-2;
    long long base=x;
    long long r=1;
    while(nn!=0)
    {
        if(nn%2)
            r*=base,r%=MOD;
        base*=base;
        base%=MOD;
        nn/=2;
    }
    return r;
}
void init()
{
    memset(l,0,sizeof(l));
    memset(r,0,sizeof(r));
    memset(w,0,sizeof(w));
    cnt=1;
    root=1;
}
void Insert(int rt,int x)
{
    if(w[rt]==0)
    {
        w[rt]=x;return ;
    }
    else
    {
        if(x>w[rt])
        {
            if(r[rt]==0)
                r[rt]=++cnt;
            Insert(r[rt],x);
        }
        else if(x<w[rt])
        {
            if(l[rt]==0)
                l[rt]=++cnt;
            Insert(l[rt],x);
        }
    }
    return ;
}
void dfs(int rt)
{
    siz[rt]=1;
    if(l[rt]!=0)
    {
        dfs(l[rt]); siz[rt]+=siz[l[rt]];
    }
    if(r[rt]!=0)
    {
        dfs(r[rt]); siz[rt]+=siz[r[rt]];
    }
}
void build()
{
    init();
    for(int i=1;i<=n;i++) Insert(root,A[i]);
}
void dfs2(int rt)
{
    if(w[rt]==0) return;
    long long get=fastpow(siz[rt]);
    res*=get;
    res%=MOD;
    dfs2(l[rt]);
    dfs2(r[rt]);
}
int main()
{
    int T;scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",&A[i]);
        build();
        res=1;
        for(long long i=1,j=m;i<=n;i++,j--) res*=j,res%=MOD;
        dfs(root);
        dfs2(root);
        printf("%lld\n",res);
    }


    return 0;
}
