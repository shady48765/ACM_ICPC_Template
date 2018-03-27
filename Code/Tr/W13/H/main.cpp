#include <iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#include<queue>
#include<cmath>
using namespace std;
int n,s,f;
double l,r;
struct _node
{
    int x,y;
    _node(){}
    _node(int x,int y):x(x),y(y){}
}node[1010];
double dist(_node a,_node b)
{
    return sqrt((double)(a.x-b.x)*(double)(a.x-b.x)+(double)(a.y-b.y)*(double)(a.y-b.y));
}
bool check(double a,double b)
{
    if(fabs(a-b)<1e-9) return true;
    else return false;
}
vector<int> G[1010];
int spfa(int s,int t)
{
    int dist[1010];
    bool inq[1010];
    for(int i=1;i<=n;i++)
        dist[i]=100000,inq[i]=false;
    queue<int> q;
    dist[s]=0;
    inq[s]=true;
    q.push(s);
    while(!q.empty())
    {
        int x=q.front();q.pop();
        inq[x]=false;
        for(int i=0;i<G[x].size();i++)
        {
            int v=G[x][i];
            if(dist[v]>dist[x]+1)
            {
                dist[v]=dist[x]+1;
                if(!inq[v]){
                    q.push(v);
                    inq[v]=true;
                }
            }
        }
    }
    return dist[t];
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%lf%lf",&n,&s,&f,&l,&r);
        int x,y;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&x,&y);
            node[i]=_node(x,y);
            G[i].clear();
        }
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                if(dist(node[i],node[j])<(l+r)||(check(dist(node[i],node[j]),(l+r))))
                {
                    G[i].push_back(j);
                    G[j].push_back(i);
                }
        int ans=spfa(s,f);
        if(ans==100000)
        printf("Impossible\n");
        else printf("%d\n",ans);
    }
    return 0;
}
