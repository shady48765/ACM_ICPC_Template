#include <cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
struct _node
{
    double x,y;
    int w;
    _node(){}
    _node(double x,double y,int w):x(x),y(y),w(w){}

}node[33];
double dist(int i,int j)
{
    return sqrt((node[i].x-node[j].x)*(node[i].x-node[j].x)+(node[i].y-node[j].y)*(node[i].y-node[j].y));
}
double dp[33][7005];
char name[1010];
double wt;
int main()
{
    int n,kase=0;
    while(scanf("%d",&n)&&n)
    {
        ++kase;
        for(int i=1;i<=n;i++)
        {
            double x,y;
            int w;
            scanf("%lf%lf%d",&x,&y,&w);
            node[i]=_node(x,y,w);
        }
        node[0]=_node(0,0,0);
        for(int i=0;i<=n;i++)
            for(int j=0;j<=6000;j++)
                dp[i][j]=(1<<30);
        dp[0][0]=0;
        for(int i=1;i<=n;i++)
            for(int j=0;j<i;j++)
                for(int k=0;k<=6000;k++)
                dp[i][k+node[i].w]=min(dp[i][k+node[i].w],dp[j][k]+dist(i,j));
        printf("Race %d\n",kase);
        while(scanf("%s%lf",name,&wt))
        {
            if(name[0]=='#'&&wt==0) break;
            int res=0;
            for(int i=0;i<=n;i++)
                for(int j=0;j<=6000;j++)
                    if(dp[i][j]+dist(i,0)<=wt)
                        res=max(res,j);
            printf("%s: %d\n",name,res);
        }
    }
    return 0;
}
