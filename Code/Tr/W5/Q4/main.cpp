#include <cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int maz[1010][1010];
int row[1010][1010],col[1010][1010],dp[1010][1010];
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)&&(n+m))
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&maz[i][j]);
        memset(row,0,sizeof(row));
        memset(col,0,sizeof(col));
        memset(dp,0,sizeof(dp));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
        {
            if(maz[i][j]==0) row[i][j]=0;
            else row[i][j]=row[i][j-1]+1;
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
        {
            if(maz[i][j]==0) col[i][j]=0;
            else col[i][j]=col[i-1][j]+1;
        }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
        {
            if(maz[i][j]==0) dp[i][j]=0;
            else
            {
                if(row[i][j]>dp[i-1][j-1]&&col[i][j]>dp[i-1][j-1]) dp[i][j]=dp[i-1][j-1]+1;
                else
                {
                    int tp=min(row[i][j],col[i][j]);
                    tp=min(tp,dp[i-1][j-1]+1);
                    dp[i][j]=tp;
                }
            }
        }
        int ans=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            ans=max(dp[i][j],ans);
        printf("%d\n",ans);
    }
    return 0;
}
