#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int maxn=1010;
vector<pair<int,int> > g[maxn];
vector<int> G[maxn];
int dp[maxn][205];
int n,m,T,k,u,v;
void dfs(int u,int fa)
{
    int temp[2][205],now=0;
    //dp[u][0]=0;
    memset(temp,-1,sizeof(temp));
    bool f=true;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa) continue;
        now^=1;
        dfs(v,u);
        if(f)
            memcpy(temp[now],dp[v],sizeof(dp[v])),f=false;
        else
        for(int t1=0;t1<=m;t1++)
        for(int t2=0;t2<=m;t2++)
        {
            if(t1+t2>m||temp[now^1][t1]==-1||dp[v][t2]==-1) continue;
            temp[now][t1+t2]=max(temp[now][t1+t2],min(temp[now^1][t1],dp[v][t2]));
        }
        memset(temp[now^1],-1,sizeof(temp[now^1]));
    }
    if(temp[now][0]==-1)
        temp[now][0]=0;
    memset(temp[now^1],-1,sizeof(temp[now^1]));
    for(int i=0;i<g[u].size();i++)
        for(int val=m;val-g[u][i].first>=0;val--)
        if(temp[now][val-g[u][i].first]!=-1)
            temp[now^1][val]=max(temp[now^1][val],temp[now][val-g[u][i].first]+g[u][i].second);
    memcpy(dp[u],temp[now^1],sizeof(dp[u]));
    for(int i=0;i<=m;i++)
        dp[u][i]=max(dp[u][i],temp[now][i]);
}
int main()
{
    //freopen("data.in","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n;i++)
        {
            G[i].clear();g[i].clear();
        }
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        scanf("%d",&m);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&k);
            for(int j=1;j<=k;j++)
            {
                scanf("%d%d",&u,&v);
                g[i].push_back(make_pair(u,v));
            }
        }
        dfs(1,-1);
        int res=0;
        for(int i=0;i<=m;i++)
            res=max(res,dp[1][i]);
        printf("%d\n",res);
    }
    return 0;
}
