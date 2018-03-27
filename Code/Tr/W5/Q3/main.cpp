#include <cstdio>
#include<algorithm>
#include<vector>
#include<cmath>
using namespace std;
struct point
{
    int x,y;
    point(){}
    point(int x,int y):x(x),y(y){}

};
vector<point> P;
double dist(int x,int y)
{
    return sqrt((P[x].x-P[y].x)*(P[x].x-P[y].x)+(P[x].y-P[y].y)*(P[x].y-P[y].y));

}
struct edge
{
    int u,v;
    double w;
    edge(){}
    edge(int u,int v,double w):u(u),v(v),w(w){}
    bool operator<(const edge& e) const
    {
        return w<e.w;
    }
};
int fa[1050];
int findfa(int x)
{
    if(x==fa[x]) return x;
    else return
        fa[x]=findfa(fa[x]);
}
vector<edge> E;
int main()
{
    int n;
    while(scanf("%d",&n)&&n)
    {
        P.clear();E.clear();
        int x,y;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&x,&y);
            P.push_back(point(x,y));
            fa[i-1]=i-1;
        }
        for(int i=0;i<n;i++) for(int j=i+1;j<n;j++)
            E.push_back(edge(i,j,dist(i,j)));
        sort(E.begin(),E.end());
        double res=0;
        for(int i=0;i<E.size();i++)
        {
            edge e=E[i];
            int u=findfa(e.u);
            int v=findfa(e.v);
            if(u==v) continue;
            fa[u]=v;
            res+=e.w;
        }
        printf("%.2f\n",res);
    }
    return 0;
}
