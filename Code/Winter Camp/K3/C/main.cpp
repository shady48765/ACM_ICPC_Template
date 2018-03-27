#include <cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
#define INF 2000100002
using namespace std;
const int maxn=200010;
int n,m,p;
struct node
{
    int id,dist,u;
    node(){}
    node(int id,int dist,int u):id(id),dist(dist),u(u){}
    bool operator<(const node& rhs ) const
    {
        return dist>rhs.dist||(dist==rhs.dist&&id<rhs.id);
    }
};
vector<int> G[maxn];
vector<int> ord;
int num[maxn];
struct edge
{
    int to,w;
    edge(){}
    edge(int to,int w):to(to),w(w){}
};
vector<edge> E;
void addedge(int u,int v,int w)
{
    E.push_back(edge(v,w));
    G[u].push_back(E.size()-1);
}
int x,y,w;
int dist[maxn];
int near[maxn];
int ID[maxn];
int now[maxn];
bool vis[maxn];
priority_queue<node> q;
void bfs()
{
    while(!q.empty())
    {
        node x=q.top();
        q.pop();
        int u=x.u;
        for(int i=0;i<G[u].size();i++)
        {
            int v=E[G[u][i]].to;
            int w=E[G[u][i]].w;
            if(dist[v]>dist[u]+w)
            {
                dist[v]=dist[u]+w;
                ID[v]=x.id;
                q.push(node(x.id,dist[v],v));
            }
            /*
            else if(dist[v]==dist[u]+w)
            {
                if(ID[v]>x.id){
                    ID[v]=x.id;
                    q.push(node(x.id,dist[v],v));
                }
            }
            */
        }
    }
}
void dfs(int u,int fa)
{
    vis[u]=true;
    for(int i=0;i<G[u].size();i++)
    {
        int v=E[G[u][i]].to;
        int w=E[G[u][i]].w;
        if(v==fa) continue;
        if(ID[v]!=ID[u])
        {
            if(dist[u]+dist[v]+w<now[ID[u]])
            {
                now[ID[u]]=dist[u]+dist[v]+w;
                near[ID[u]]=ID[v];
            }
            else if(dist[u]+dist[v]+w==now[ID[u]])
            {
                near[ID[u]]=min(near[ID[u]],ID[v]);
            }

            if(dist[u]+dist[v]+w<now[ID[v]])
            {
                now[ID[v]]=dist[u]+dist[v]+w;
                near[ID[v]]=ID[u];
            }
            else if(dist[u]+dist[v]+w==now[ID[v]])
            {
                near[ID[v]]=min(near[ID[v]],ID[u]);
            }
        }
        if(!vis[v]) dfs(v,u);
    }
}
int main()
{
     //freopen("data.in","r",stdin);
   //printf("%d\n",INF);
    memset(vis,false,sizeof(vis));
    memset(near,-1,sizeof(near));
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&w);
        addedge(x,y,w);
        addedge(y,x,w);
    }
    for(int i=1;i<=n;i++) dist[i]=INF,now[i]=INF,near[i]=-1;
    for(int i=1;i<=p;i++)
    {
        scanf("%d",&x);
        ord.push_back(x);
        ID[x]=x;
        q.push(node(x,0,x));
        dist[x]=0;
    }
    bfs();
    dfs(1,-1);
    for(int i=0;i<p;i++)
        printf("%d\n",near[ord[i]]);

    return 0;
}
