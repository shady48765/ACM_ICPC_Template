#include <iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
#define INF (1<<30)
using namespace std;
int dp1[2][201010],dp2[2][201010];
int main()
{
    //freopen("data.in","r",stdin);
    int n,x,y;
    while(scanf("%d",&n)&&n)
    {
        int cur=0;
        memset(dp1,-0x3f,sizeof(dp1));
        memset(dp2,0x3f,sizeof(dp2));
        dp1[cur][100000]=dp2[cur][100000]=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&x,&y);
            memset(dp1[cur^1],-0x3f,sizeof(dp1[cur^1]));
            memset(dp2[cur^1],0x3f,sizeof(dp2[cur^1]));
            for(int j=1;j<=200000;j++)
            {
                if(dp1[cur][j]>-100000){
                dp1[cur^1][j+x]=max(dp1[cur^1][j+x],dp1[cur][j]+y);
                dp1[cur^1][j-x]=max(dp1[cur^1][j-x],dp1[cur][j]-y);
                }
                if(dp2[cur][j]<100000){
                dp2[cur^1][j+x]=min(dp2[cur^1][j+x],dp2[cur][j]+y);
                dp2[cur^1][j-x]=min(dp2[cur^1][j-x],dp2[cur][j]-y);
                }
            }
            cur^=1;
        }
        double ans=0;
        for(int i=1;i<=200000;i++)
        {
            if(dp1[cur][i]>-100000)
            ans=max(ans,sqrt((double)(i-100000)*(i-100000)+(double)dp1[cur][i]*dp1[cur][i]));
            if(dp2[cur][i]<100000)
            ans=max(ans,sqrt((double)(i-100000)*(i-100000)+(double)dp2[cur][i]*dp2[cur][i]));
        }
        printf("%.3f\n",ans);
    }
    return 0;
}
