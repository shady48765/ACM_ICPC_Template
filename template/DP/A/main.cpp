#include <iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
const int maxn=300010;
vector<int> G[maxn];
int n,q,u,v,T;
int siz[maxn],fa[maxn];
long long ans[maxn],tans[maxn],val[maxn],r[maxn],Time[maxn];
void dfs(int u,int f)
{
    siz[u]=1;
    r[u]=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==f) continue;
        dfs(v,u);
        fa[v]=u;
        siz[u]+=siz[v];
        r[u]+=(r[v]+siz[v]);
    }
}
void get(int u,int f)
{
    if(val[u]!=-1)
        tans[u]=val[u]*siz[u]+r[u]*Time[u];
    else
        tans[u]=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==f) continue;
        get(v,u);
        tans[u]+=tans[v];
    }
}
void dfs2(int u,int f,int Siz,long long trf)
{
    if(f!=-1)
    {
        ans[u]=ans[f];
        if(val[f]!=-1)
            ans[u]-=(val[f]*siz[u]+Time[f]*(r[u]+siz[u]));
        if(val[u]!=-1)
            ans[u]+=(val[u]*Siz+Time[u]*trf);
    }
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==f) continue;
        //printf("%d \n",r[v]);
        //printf("%d %d %d %d %d %d\n",u,Siz,trf,r[v],siz[v],siz[u]);
        dfs2(v,u,Siz+siz[u]-siz[v],r[u]+trf-r[v]-siz[v]+Siz+siz[u]-siz[v]);
    }
}

vector<int> O;
int main()
{
    //freopen("data.in","r",stdin);
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        scanf("%d%d",&n,&q);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        memset(val,-1,sizeof(val));
        memset(Time,0,sizeof(Time));
        for(int i=1;i<=q;i++)
        {
            scanf("%d%d",&u,&v);
            if(val[u]==-1)
                val[u]=v;
            else
                val[u]+=v;
            Time[u]++;
        }
        dfs(1,-1);
        get(1,-1);
        ans[1]=tans[1];
        dfs2(1,-1,0,0);
        O.clear();
        long long mini=1LL<<60;
        /*
        for(int i=1;i<=n;i++)
        {
            printf("%lld ",ans[i]);
        }
        printf("\n");
        for(int i=1;i<=n;i++)
        {
            dfs(i,-1);
            get(i,-1);
            printf("%lld ",tans[i]);
        }
        printf("\nend\n");
        /*/
        for(int i=1;i<=n;i++)
        {
            mini=min(mini,ans[i]);
        }
        for(int i=1;i<=n;i++)
            if(ans[i]==mini) O.push_back(i);
        printf("Case #%d: %lld\n",kase,mini);
        for(int i=0;i<O.size();i++)
        {
            if(i) printf(" ");
            printf("%d",O[i]);
        }
        printf("\n");
        //*/
    }
    return 0;
}
