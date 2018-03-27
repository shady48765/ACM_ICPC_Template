#include <iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
const int maxn=150;
const int inf=1<<28;
vector<int> G[maxn];
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
int n,m,c;
int fa[105];
void init()
{
    E.clear();
    int u,v,w;
    for(int i=1;i<=n;i++)
    {
        fa[i]=i;G[i].clear();
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        addedge(u,v,w);
    }
}
struct node
{
    int x,y;
    node(){}
    node(int x,int y):x(x),y(y){}
};
int spfa(int s,int t)
{
    bool inq[105][1010];
    int dist[105][1010];
    for(int i=1;i<=n;i++)
        for(int j=0;j<=m;j++)
            dist[i][j]=inf;
    memset(inq,false,sizeof(inq));
    dist[s][0]=0;
    queue<node> q;
    inq[s][0]=true;
    dist[s][0]=0;
    q.push(node(s,0));
    while(!q.empty())
    {
        node now=q.front();q.pop();
        inq[now.x][now.y]=false;
        for(int i=0;i<G[now.x].size();i++)
        {
            int e=G[now.x][i];
            if(E[e].w+dist[now.x][now.y]<dist[E[e].to][now.y])
            {
                dist[E[e].to][now.y]=E[e].w+dist[now.x][now.y];
                if(!inq[E[e].to][now.y])
                {
                    q.push(node(E[e].to,now.y));
                    inq[E[e].to][now.y]=true;
                }
            }
            if(dist[now.x][now.y]<dist[E[e].to][now.y+1])
            {
                dist[E[e].to][now.y+1]=dist[now.x][now.y];
                if(!inq[E[e].to][now.y+1])
                {
                    q.push(node(E[e].to,now.y+1));
                    inq[E[e].to][now.y+1]=true;
                }
            }
        }
    }
    for(int i=0;i<=m;i++)
        if(dist[t][i]<=c) return i;
}
int main()
{
    //freopen("data.in","r",stdin);
    while(scanf("%d%d%d",&n,&m,&c)&&(n+m+c))
    {
        init();
        printf("%d\n",spfa(1,n));
    }
    return 0;
}
