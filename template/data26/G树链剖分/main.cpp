#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
#define dec DEC
using namespace std;
const int maxn=100010;
int n,m,u,v,c;
int dep[maxn],fa[maxn],p[maxn],fp[maxn],son[maxn],siz[maxn],top[maxn],dfn;
vector<int> G[maxn];
vector<int> add[maxn],dec[maxn];
void init()
{
    dfn=0;
    memset(G,0,sizeof(G));
    memset(add,0,sizeof(add));
    memset(dec,0,sizeof(dec));
    memset(son,0,sizeof(son));
    memset(fa,0,sizeof(fa));
}
void dfs(int u,int d)
{
    dep[u]=d;
    siz[u]=1;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa[u]) continue;
        fa[v]=u;
        dfs(v,d+1);
        if(siz[v]>siz[son[u]])
            son[u]=v;
    }
}
void dfs2(int u,int tp)
{
    top[u]=tp;
    p[u]=++dfn;
    fp[p[u]]=u;
    if(!son[u]) return;
    dfs2(son[u],tp);
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==son[u]||v==fa[u]) continue;
        dfs2(v,v);
    }
}
void fupdate(int u,int v,int c)
{
    int f1=top[u],f2=top[v];
    while(f1!=f2)
    {
        if(dep[f1]<dep[f2])
        {
            swap(f1,f2);
            swap(u,v);
        }
        add[p[f1]].push_back(c);
        dec[p[u]+1].push_back(c);
        u=fa[f1];
        f1=top[u];
    }
    if(dep[u]>dep[v]) swap(u,v);
    add[p[u]].push_back(c);
    dec[p[v]+1].push_back(c);
}
int id[maxn<<2],mx[maxn<<2],ans[maxn];
void pushup(int o)
{
    if(mx[o<<1]<mx[o<<1|1])
    {
        mx[o]=mx[o<<1|1];
        id[o]=id[o<<1|1];
    }
    else
    {
        mx[o]=mx[o<<1];
        id[o]=id[o<<1];
    }
}
void build(int o,int l,int r)
{
    if(l==r)
    {
        mx[o]=0;id[o]=l;
    }
    else
    {
        int mid=(l+r)>>1;
        build(o<<1,l,mid);
        build(o<<1|1,mid+1,r);
        pushup(o);
    }
}
void update(int o,int p,int l,int r,int v)
{
    if(l==r)
    {
        mx[o]+=v;
    }
    else
    {
        int mid=(l+r)>>1;
        if(p<=mid)
            update(o<<1,p,l,mid,v);
        else
            update(o<<1|1,p,mid+1,r,v);
        pushup(o);
    }
}
int main()
{
    while(scanf("%d%d",&n,&m)&&(n+m))
    {
        init();
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1,1);
        dfs2(1,1);
        while(m--)
        {
            scanf("%d%d%d",&u,&v,&c);
            fupdate(u,v,c);
        }
        build(1,1,maxn-1);
        for(int i=1;i<=n;i++)
        {
            for(int j=0;j<add[i].size();j++)
            {
                update(1,add[i][j],1,maxn-1,1);
            }
            for(int j=0;j<dec[i].size();j++)
            {
                update(1,dec[i][j],1,maxn-1,-1);
            }
            u=fp[i];
            if(mx[1]==0) ans[u]=0;
            else ans[u]=id[1];
        }
        for(int i=1;i<=n;i++)
            printf("%d\n",ans[i]);
    }
    return 0;
}
