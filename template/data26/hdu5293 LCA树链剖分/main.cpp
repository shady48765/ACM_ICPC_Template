#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <iostream>
#include <cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int maxn=100010;
int T,n,m,u,v,w,fa[maxn][20];
int siz[maxn],son[maxn],dep[maxn],top[maxn],idx[maxn],cnt;
int dd[maxn],sm[maxn];
vector<int> G[maxn];
vector<int> g[maxn];
void dfs(int u,int f,int d)
{
    dep[u]=d;
    siz[u]=1;
    son[u]=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==f) continue;
        fa[v][0]=u;
        dfs(v,u,d+1);
        if(siz[son[u]]<siz[v]) son[u]=v;
        siz[u]+=siz[v];
    }
}
void dfs2(int u,int tp)
{
    ++cnt;
    idx[u]=cnt;
    top[u]=tp;
    if(son[u])
        dfs2(son[u],tp);
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa[u][0]||v==son[u]) continue;
        dfs2(v,v);
    }
}
void dfs3(int u)
{
    for(int i=1;i<20;i++)
    {
        if(!fa[u][i-1]) break;
        fa[u][i]=fa[fa[u][i-1]][i-1];
    }
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa[u][0]) continue;
        dfs3(v);
    }
}
int Lca(int u,int v)
{
    while(dep[u]!=dep[v])
    {
        if(dep[u]<dep[v]) swap(u,v);
        for(int i=19;i>=0;i--)
            if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
    }
    if(u==v) return u;
    for(int i=19;i>=0;i--)
        if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
    u=fa[u][0];
    return u;
}
struct link
{
    int u,v,w,lca;
    link(int u,int v,int w,int lca):u(u),v(v),w(w),lca(lca){}
    bool operator<(const link& rhs) const
    {
        return dep[lca]>dep[rhs.lca];
    }
};
struct segtree
{
    int sum[maxn<<2];
    void init()
    {
        memset(sum,0,sizeof(sum));
    }
    void pushup(int o)
    {
        sum[o]=sum[o<<1]+sum[o<<1|1];
    }
    void update(int o,int l,int r,int p,int v)
    {
        if(l==r)
        {
            sum[o]+=v;
        }
        else
        {
            int mid=(l+r)>>1;
            if(p<=mid)
                update(o<<1,l,mid,p,v);
            if(p>mid)
                update(o<<1|1,mid+1,r,p,v);
            pushup(o);
        }
    }
    int query(int o,int l,int r,int L,int R)
    {
        if(L<=l&&r<=R)
        {
            return sum[o];
        }
        else
        {
            int mid=(l+r)>>1,res=0;
            if(L<=mid)
                res+=query(o<<1,l,mid,L,R);
            if(R>mid)
                res+=query(o<<1|1,mid+1,r,L,R);
            return res;
        }
    }
}tree1,tree2;
bool ok=false;
int fquery(int u,int v,segtree& tree)
{
    int f1=top[u],f2=top[v],res=0;
    while(f1!=f2)
    {
        if(dep[f1]<dep[f2])
        {
            swap(u,v);
            swap(f1,f2);
        }
        res+=tree.query(1,1,n,idx[f1],idx[u]);
        u=fa[f1][0],f1=top[u];
    }
    if(dep[u]<dep[v])
    {
        swap(u,v);
    }
    res+=tree.query(1,1,n,idx[v],idx[u]);
    return res;
}
vector<link> L;
void dfs4(int u)
{
    sm[u]=dd[u]=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa[u][0]) continue;
        dfs4(v);
        sm[u]+=dd[v];
    }
    tree2.update(1,1,n,idx[u],sm[u]);
    dd[u]=sm[u];
    for(int i=0;i<g[u].size();i++)
    {
        int uu=L[g[u][i]].u;
        int vv=L[g[u][i]].v;
        int ww=L[g[u][i]].w;
        dd[u]=max(dd[u],ww+fquery(uu,vv,tree2)-fquery(uu,vv,tree1));
    }
    tree1.update(1,1,n,idx[u],dd[u]);
}
void debug(int u)
{
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa[u][0]) continue;
        debug(v);
    }
}
int main()
{
    //freopen("data.in","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
        {
            G[i].clear();
            g[i].clear();
        }
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        memset(fa,0,sizeof(fa));
        cnt=0;
        dfs(1,-1,1);
        dfs2(1,1);
        dfs3(1);
        L.clear();
        tree1.init();
        tree2.init();
        for(int i=0;i<m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            L.push_back(link(u,v,w,Lca(u,v)));
        }
        sort(L.begin(),L.end());
        for(int i=0;i<L.size();i++) g[L[i].lca].push_back(i);
        dfs4(1);
        printf("%d\n",dd[1]);
    }
    return 0;
}
