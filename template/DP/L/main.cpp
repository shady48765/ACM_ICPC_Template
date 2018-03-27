#include <iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
#include<vector>
using namespace std;
const int maxn=10010;
const double eps=1e-9;
vector<int> G[maxn];
int n,u,v;
double ki[maxn],ei[maxn];
struct res
{
    double A,B,C;
    res(){}
    res(double A,double B,double C):A(A),B(B),C(C){}
}node[maxn];
double ret;
res dfs(int u,int fa)
{
    if(G[u].size()==1&&fa!=-1)
    return node[u]=res(ki[u],1-ki[u]-ei[u],1-ki[u]-ei[u]);
    if(fa!=-1)
    {
        double A=ki[u];
        double B=(1-ki[u]-ei[u])/G[u].size();
        double C=(1-ki[u]-ei[u]);
        double p=B;
        double q=1.0;
        for(int i=0;i<G[u].size();i++)
        {
            int v=G[u][i];
            if(v==fa) continue;
            res tp=dfs(v,u);
            node[v]=tp;
            A+=tp.A*p;
            q-=tp.B*p;
            C+=tp.C*p;
        }
        A/=q;
        B/=q;
        C/=q;
        return res(A,B,C);
    }
    else
    {
        double left=1.0,right=1,p=1.0/G[u].size();
        for(int i=0;i<G[u].size();i++)
        {
            int v=G[u][i];
            if(v==fa) continue;
            res tp=dfs(v,u);
            left-=(tp.A+tp.B)*p;
            right+=tp.C*p;
        }
        return res(right,left,0);
    }
}
void debug(int u,int fa)
{
    cout<<u<<" "<<node[u].A<<" "<<node[u].B<<" "<<node[u].C<<endl;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa) continue;
        debug(v,u);
    }
}
int main()
{
    //freopen("data.in","r",stdin);
    int T;
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<=n-1;i++)
        {
            scanf("%d%d",&u,&v);
            G[u].push_back(v);
            G[v].push_back(u);
        }
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&u,&v);
            ki[i]=u/100.0;
            ei[i]=v/100.0;
        }
        res tp=dfs(1,-1);
        //debug(1,-1);
        if(tp.B<eps)
            printf("Case %d: impossible\n",kase);
        else
            printf("Case %d: %.6f\n",kase,tp.A/tp.B);
    }
    return 0;
}
