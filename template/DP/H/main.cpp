#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
const int inf=100000000;
vector<int> G[505];
int T,n,k,u,v,w;
struct edge
{
    int u,v,w;
    edge(){}
    edge(int u,int v,int w):u(u),v(v),w(w){}
};
vector<edge> E;
void addedge(int u,int v,int w)
{
    E.push_back(edge(u,v,w));
    G[u].push_back(E.size()-1);
}
int dp[505][3];
void dfs(int u,int fa)
{
    for(int i=0;i<3;i++) dp[u][i]=i*k;
    for(int i=0;i<G[u].size();i++)
    {
        int v=E[G[u][i]].v;
        int w=E[G[u][i]].w;
        if(v==fa) continue;
        dfs(v,u);
        int temp[3]={inf,inf,inf};
        temp[0]=dp[u][1]+dp[v][1]-k+w;
        temp[0]=min(temp[0],dp[u][2]+dp[v][2]-2*k+2*w);
        temp[1]=dp[u][0]+dp[v][1]+w;
        temp[1]=min(temp[1],dp[u][1]+dp[v][2]-k+2*w);
        temp[1]=min(temp[1],dp[u][2]+dp[v][1]-k+w);
        temp[2]=dp[u][0]+dp[v][2]+2*w;
        temp[2]=min(temp[2],dp[u][1]+dp[v][1]+w);
        temp[2]=min(temp[2],dp[u][2]+dp[v][2]+2*w-k);
        memcpy(dp[u],temp,sizeof(temp));
    }
}
int main()
{
    //freopen("data.in","r",stdin);
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        scanf("%d%d",&n,&k);
        for(int i=0;i<n;i++) G[i].clear();
        E.clear();
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            addedge(u,v,w);
            addedge(v,u,w);
        }
        memset(dp,0,sizeof(dp));
        dfs(0,-1);
        int res=inf;
        for(int i=0;i<3;i++) res=min(res,dp[0][i]);
        printf("Case #%d: %d\n",kase,res);

    }
    return 0;
}
