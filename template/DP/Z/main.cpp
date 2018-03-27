#include <cstdio>
#include<vector>
#include<cstring>
#include<queue>
using namespace std;
int T,n,m,k,fins;
int vis[55][(1<<8)+10][(1<<8)+10];
int mp[55][55],ticket[55],Time[10][2],pos[55];
vector<int> G[55];
void init()
{
    for(int i=1;i<=n;i++) G[i].clear();
    memset(vis,-1,sizeof(vis));
    memset(mp,0,sizeof(mp));
    memset(pos,0,sizeof(pos));
    memset(ticket,0,sizeof(ticket));
}
struct node
{
    int u,sta,ti,time;
    node(){}
    node(int u,int sta,int ti,int time):u(u),sta(sta),ti(ti),time(time){}
    bool operator<(const node& rhs) const
    {
        return time>rhs.time;
    }
}now,nxt;
int bfs()
{
    int nsta,nti,ntime;
    vis[1][0][ticket[1]]=0;
    priority_queue<node> q;
    q.push(node(1,0,ticket[1],0));
    while(!q.empty())
    {
        now=q.top();q.pop();
        int u=now.u;
        if(now.sta==fins&&u==1) return now.time;
        for(int i=0;i<k;i++)if((pos[u]&(1<<i))&&!(now.sta&(1<<i)))
        {
            if(vis[u][now.sta|(1<<i)][now.ti]==-1||vis[u][now.sta|(1<<i)][now.ti]>now.time+Time[i][0])
            {
                vis[u][now.sta|(1<<i)][now.ti]=now.time+Time[i][0];
                q.push(node(u,now.sta|(1<<i),now.ti|(1<<i),now.time+Time[i][0]));
            }
        }
        for(int i=0;i<G[u].size();i++)
        {
            int v=G[u][i];
            nsta=now.sta;
            nti=now.ti|ticket[v];
            ntime=now.time+mp[u][v];
            for(int j=0;j<k;j++)
            {
                int tr=(1<<j);
                if(!(nsta&tr)&&(pos[v]&tr)&&(nti&tr))
                    nsta|=tr,ntime+=Time[j][1];
            }
            if(vis[v][nsta][nti]==-1||vis[v][nsta][nti]>ntime)
            {
                vis[v][nsta][nti]=ntime;
                q.push(node(v,nsta,nti,ntime));
            }
        }
    }
    return -1;
}
int main()
{
    int u,v,w;
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        scanf("%d%d%d",&n,&m,&k);init();
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            mp[u][v]=mp[v][u]=w;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        for(int i=0;i<k;i++)
        {
            scanf("%d",&u);
            pos[u]|=(1<<i);
            scanf("%d%d",&Time[i][0],&Time[i][1]);
            scanf("%d",&u);
            for(int j=1;j<=u;j++)
            {
                scanf("%d",&v);
                ticket[v]|=(1<<i);
            }
        }
        fins=(1<<k)-1;
        printf("Case #%d: %d\n",kase,bfs());
    }
    return 0;
}
