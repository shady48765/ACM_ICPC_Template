#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
using namespace std;
const int maxn=50010;
const int mod=1000000007;
int T,n,u,v,L[55],R[55];
int dp[105][maxn],inv[105][maxn],ans[55],tot;
bool vis[105];
vector<int> have[maxn];
void add(int &x,int y)
{
    x+=y;
    if(x>=mod) x-=mod;
}
void seive()
{
    for(int i=2;i<maxn;i++)if(!have[i].size())
        for(int j=i;j<maxn;j+=i)
            have[j].push_back(i);
}
int head[55],to[105],nxt[105];
void init()
{
    tot=0;
    memset(head,-1,sizeof(head));
}
void addedge(int u,int v)
{
    to[tot]=v;
    nxt[tot]=head[u];
    head[u]=tot++;
}
int calc(int i,int val)
{
    int tp=0;
    int mask=1<<have[val].size();
    for(int s=0;s<mask;s++)
    {
        int res=1,ct=0;
        for(int q=0;q<have[val].size();q++)
        {
            if(s&(1<<q)) res*=have[val][q],ct^=1;
        }
        if(ct) add(tp,(mod-inv[i][res]));
        else add(tp,inv[i][res]);
    }
    return tp;
}
void dfs(int id)
{
    if(vis[id]) return ;
    vis[id]=true;
    int u=to[id];
    for(int j=L[u];j<=R[u];j++)
    {
        dp[id][j]=1;
        for(int i=head[u];i!=-1;i=nxt[i])
        {
            if((i^1)==id) continue;
            dfs(i);
            dp[id][j]=1LL*dp[id][j]*calc(i,j)%mod;
        }
    }
    for(int i=1;i<maxn;i++)
        for(int j=i;j<maxn;j+=i)
            add(inv[id][i],dp[id][j]);
}
int main()
{
    //freopen("data.in","r",stdin);
    seive();
    scanf("%d",&T);
    while(T--)
    {
        memset(dp,0,sizeof(dp));
        memset(inv,0,sizeof(inv));
        memset(vis,false,sizeof(vis));
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            scanf("%d",&L[i]);
        for(int j=1;j<=n;j++)
            scanf("%d",&R[j]);
        init();
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d",&u,&v);
            addedge(u,v);
            addedge(v,u);
        }
        for(int i=0;i<tot;i++) dfs(i);
        for(int i=1;i<=n;i++)
        {
            ans[i]=0;
            for(int j=L[i];j<=R[i];j++)
            {
                int ct=1;
                for(int k=head[i];k!=-1;k=nxt[k])
                    ct=1L*ct*calc(k,j)%mod;
                add(ans[i],1LL*j*ct%mod);
            }
        }
        for(int i=1;i<=n;i++)
            if(i==n)
            printf("%d\n",ans[i]);
        else printf("%d ",ans[i]);
    }
    return 0;
}
