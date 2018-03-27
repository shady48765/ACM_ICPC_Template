#include <iostream>
#include<cstdio>
#include<vector>
#include<cstring>
#define MOD 1000000000
using namespace std;
long long dp[105][2][105];
vector<int> G[105];
int n,u,v;
void dfs(int u,int fa)
{
    dp[u][0][0]=1;
    dp[u][1][1]=1;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa) continue;
        dfs(v,u);
        long long Tp[105],Tp2[105];
        memset(Tp,0,sizeof(Tp));
        for(int k=1;k<=n;k++)
        {
            for(int i=0;i<=n&&i+k<=n;i++)
                Tp[i+k]+=dp[u][0][i]*(dp[v][0][k]+dp[v][1][k])%MOD;
        }
        for(int i=1;i<=n;i++)
            dp[u][0][i]+=Tp[i],dp[u][0][i]%=MOD;
        memset(Tp,0,sizeof(Tp));
        memset(Tp2,0,sizeof(Tp2));
        for(int k=1;k<=n;k++)
        {
            for(int i=1;i<=n&&i+k<=n;i++)
            {
                Tp[i+k-1]+=dp[u][1][i]*dp[v][1][k]%MOD;
                Tp2[i+k]+=dp[u][1][i]*(dp[v][1][k]+dp[v][0][k])%MOD;
            }
        }
        for(int i=1;i<=n;i++)
            dp[u][1][i]+=(Tp[i]+Tp2[i]),dp[u][1][i]%=MOD;
    }
}
int main()
{
    freopen("subtrees.in","r",stdin);
    freopen("subtrees.out","w",stdout);
    scanf("%d",&n);
    memset(dp,0,sizeof(dp));
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,-1);
    for(int i=1;i<=n;i++)
        printf("%I64d\n",(dp[1][0][i]+dp[1][1][i])%MOD);
    return 0;
}
