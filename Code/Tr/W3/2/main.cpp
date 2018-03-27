#include <iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<vector>
#define MOD 1000000007
using namespace std;
int fa[1010],siz[1010],root;
vector<int> G[1010];
long long res;
void dfs(int u)
{
    siz[u]=1;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        dfs(v);
        siz[u]+=siz[v];
    }
}
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
void dfs2(int u)
{
    long long t=fastpow(siz[u]);
    res*=t,res%=MOD;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        dfs2(v);
    }
}
int main()
{
    int T,n;
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        scanf("%d",&n);
        int u,v;
        memset(G,0,sizeof(G));
        memset(fa,0,sizeof(fa));
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            fa[v]=u;
        }
        for(int i=1;i<=n;i++) if(fa[i]==0) root=i;
        res=1;
        for(long long i=1;i<=n;i++) res*=i,res%=MOD;
        dfs(root);
        dfs2(root);
        printf("Case %d: %lld\n",kase,res);
    }
    return 0;
}
