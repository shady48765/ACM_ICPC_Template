#include <cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int maxn=50010;
int n,m,p,cnt;
int w[maxn],son[maxn],siz[maxn],top[maxn],dep[maxn],fa[maxn];
int tag[maxn<<2];
vector<int> G[maxn];
void init()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) G[i].clear();
    int u,v;
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d",&u,&v);
        u++,v++;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    memset(tag,0,sizeof(tag));
    cnt=0;
}
void dfs(int u)
{
    siz[u]=1;son[u]=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa[u]) continue;
        fa[v]=u;
        dep[v]=dep[u]+1;
        dfs(v);
        if(siz[v]>siz[son[u]]) son[u]=v;
        siz[u]+=siz[v];
    }
}
void build(int u,int tp)
{
    w[u]=++cnt;top[u]=tp;
    if(son[u]!=0)
    {
        build(son[u],tp);
    }
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==son[u]||v==fa[u]) continue;
        build(v,v);
    }
}
void pushdown(int o)
{
    if(tag[o]!=0)
    {
        tag[o<<1]+=tag[o];
        tag[o<<1|1]+=tag[o];
        tag[o]=0;
    }
}
void update(int o,int l,int r,int L,int R,int x)
{
    if(L<=l&&r<=R)
    {
        tag[o]+=x;
    }
    else
    {
        pushdown(o);
        int mid=(l+r)>>1;
        if(L<=mid)
            update(o<<1,l,mid,L,R,x);
        if(R>mid)
            update(o<<1|1,mid+1,r,L,R,x);
    }
}
int query(int o,int l,int r,int pos)
{
    if(l==r)
        return tag[o];
    else
    {
        pushdown(o);
        int mid=(l+r)>>1;
        if(pos<=mid)
            return query(o<<1,l,mid,pos);
        else
            return query(o<<1|1,mid+1,r,pos);
    }
}
void fupdate(int u,int v,int x)
{
    int f1=top[u],f2=top[v];
    while(f1!=f2)
    {
        if(dep[f1]<dep[f2])
        {
            swap(f1,f2);swap(u,v);
        }
        update(1,1,cnt,w[f1],w[u],x);
        u=fa[f1];f1=top[u];
    }
    if(dep[u]>dep[v])
        swap(u,v);
    update(1,1,cnt,w[u],w[v],x);
}
int main()
{
    //freopen("data.in","r",stdin);
    int T;
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        init();
        dfs(1);
        build(1,1);
        int q;
        scanf("%d",&q);
        int uu,vv,ww;
        while(q--)
        {
            scanf("%d%d%d",&uu,&vv,&ww);
            uu++,vv++;
            fupdate(uu,vv,ww);
        }
        printf("Case #%d:\n",kase);
        for(int i=1;i<=n;i++)
            printf("%d\n",query(1,1,cnt,w[i]));
    }
    return 0;
}
