#pragma comment(linker, "/STACK:102400000,102400000")
#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int maxn=100010;
int n;
queue<int> q;
struct edge
{
    int to,w;
    edge(){}
    edge(int to,int w):to(to),w(w){}
};
vector<edge> E;
vector<int> G[maxn];
int have[maxn],near[maxn],id[maxn];
void addedge(int u,int v,int w)
{
    E.push_back(edge(v,w));
    G[u].push_back(E.size()-1);
}
int siz[maxn],SIZE,mx[maxn],root,ans[maxn];
bool done[maxn];
void init()
{
    E.clear();
    while(!q.empty()) q.pop();
    for(int i=1;i<=n;i++) G[i].clear();
    int u,v,w;
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        addedge(u,v,w);
        addedge(v,u,w);
    }
    memset(ans,0,sizeof(ans));
    memset(done,false,sizeof(done));
    memset(near,0x3f,sizeof(near));
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&have[i]);
        if(have[i])
        {
            q.push(i);
            near[i]=0;
            id[i]=i;
        }
    }
    mx[0]=9999999;
}
void spfa()
{
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=0;i<G[u].size();i++)
        {
            int v=E[G[u][i]].to;
            int w=E[G[u][i]].w;
            if(near[v]>near[u]+w||(near[v]==near[u]+w&&id[v]>id[u]))
            {
                near[v]=near[u]+w;
                id[v]=id[u];
                q.push(v);
            }
        }
    }
}
void getroot(int u,int fa)
{
    siz[u]=1;mx[u]=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=E[G[u][i]].to;
        int w=E[G[u][i]].w;
        if(v==fa||done[v]) continue;
        getroot(v,u);
        siz[u]+=siz[v];
        mx[u]=max(mx[u],siz[v]);
    }
    mx[u]=max(mx[u],SIZE-siz[u]);
    if(mx[u]<mx[root]) root=u;
}
int cnt=0;
int pt[maxn],di[maxn];
pair<int,int> Pair[maxn];
void get(int u,int fa,int d)
{
    if(!have[u])
    {
        pt[cnt]=u;
        di[cnt]=d;
        Pair[cnt++]=make_pair(near[u]-d,id[u]);
    }
    for(int i=0;i<G[u].size();i++)
    {
        int v=E[G[u][i]].to;
        int w=E[G[u][i]].w;
        if(v==fa||done[v]) continue;
        get(v,u,d+w);
    }
}
void calc(int f)
{
    sort(Pair,Pair+cnt);
    for(int i=0;i<cnt;i++)
    {
        int k=lower_bound(Pair,Pair+cnt,make_pair(di[i],pt[i]))-Pair;
        ans[pt[i]]+=f*(cnt-k);
    }
}
void work(int u)
{
    cnt=0;
    get(u,-1,0);
    calc(1);
    done[u]=true;
    for(int i=0;i<G[u].size();i++)
    {
        int v=E[G[u][i]].to;
        int w=E[G[u][i]].w;
        if(done[v]) continue;
        cnt=0;
        get(v,-1,w);
        calc(-1);
        SIZE=siz[v];
        getroot(v,root=0);
        work(root);
    }
}
int main()
{
    //freopen("data.in","r",stdin);
    while(scanf("%d",&n)!=EOF)
    {
        init();
        spfa();
        SIZE=n;
        getroot(1,root=0);
        work(root);
        int res=0;
        for(int i=1;i<=n;i++)
            res=max(res,ans[i]);
        printf("%d\n",res);
    }
    return 0;
}
