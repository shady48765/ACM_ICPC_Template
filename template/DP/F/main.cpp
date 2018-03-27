#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
typedef long long LL;
const int mod=1000000007;
vector<int> G[44],g[44];
int n,m,u,v;
LL C[44][44];
LL dp[1<<21];
int num[44],lim[44];
LL DP(vector<int>& Gg)
{
    sort(Gg.begin(),Gg.end());
    dp[0]=1;
    int n=Gg.size();
    for(int i=0;i<n;i++)
        for(int j=0;j<g[Gg[i]].size();j++)
            num[g[Gg[i]][j]]=lower_bound(Gg.begin(),Gg.end(),g[Gg[i]][j])-Gg.begin();
    memset(lim,0,sizeof(lim));
    for(int i=0;i<n;i++)
        for(int j=0;j<g[Gg[i]].size();j++)
            lim[i]|=1<<num[g[Gg[i]][j]];
    int maxS=1<<n;
    for(int s=0;s<maxS;s++)
        for(int i=0;i<n;i++) if(!(s>>i&1))
        {
            if(lim[i]&(~s)) continue;
            dp[s^(1<<i)]+=dp[s];
            if(dp[s^(1<<i)]>=mod)
                dp[s^(1<<i)]-=mod;
        }
    return dp[maxS-1]%mod;
}
void calc()
{
    C[0][0]=1;
    for(int i=1;i<=40;i++)
        for(int j=0;j<=i;j++)
            if(j==0||j==i) C[i][j]=1;
            else C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;

}
vector<int> table;
bool vis[44];
void dfs(int u,int fa)
{
    table.push_back(u);
    vis[u]=true;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa||vis[v]) continue;
        dfs(v,u);
    }
}
int main()
{
    calc();
    while(scanf("%d%d",&n,&m)!=EOF)
    {
        for(int i=1;i<=n;i++) G[i].clear(),g[i].clear();
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
            g[u].push_back(v);
        }
        memset(vis,false,sizeof(vis));
        int sum=n,sz;
        LL res=1;
        for(int i=1;i<=n;i++)
        {
            if(vis[i]) continue;
            table.clear();
            dfs(i,-1);
            sz=table.size();
            for(int i=0;i<1<<sz;i++) dp[i]=0;
            res*=DP(table)*C[sum][sz]%mod;
            res%=mod;
            sum-=sz;
        }
        printf("%I64d\n",res);
    }
    return 0;
}
