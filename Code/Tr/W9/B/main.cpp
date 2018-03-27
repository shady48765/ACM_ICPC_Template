#include <cstdio>
#include<algorithm>
using namespace std;
const int inf=(1<<27);
int n,t,x,k,rx,rt;
int dp[44][4];
int main()
{
       // freopen("data.in","r",stdin);
    while(scanf("%d",&n)&&n)
    {
        rx=rt=0;
        for(int i=0;i<=n+1;i++)
            for(int j=0;j<4;j++)
                dp[i][j]=inf;
        for(int i=1;i<=n+1;i++)
        {
            if(i<=n)
            scanf("%d%d",&x,&t);
            else
                x=0,t=inf;
            for(int j=2;j<=3;j++)
                if((j)*abs(x-rx)<=abs(t-rt))
            dp[i][j]=min(dp[i][j],dp[i-1][j-1]+abs(x-rx));
            for(int j=1;j<=3;j++)
                if((j+1)*rx+x<=abs(t-rt))
            dp[i][1]=min(dp[i][1],dp[i-1][j]+rx+x);
            if(i==1&&x<=t) dp[i][1]=x;
            rx=x,rt=t;
        }
        bool f=true;
        for(int i=1;i<=n;i++){
            bool ok=false;
            for(int j=1;j<=3;j++)
                if(dp[i][j]<inf) ok=true;
            if(!ok&&f)
                printf("NG %d\n",i),f=false;
        }
        int ans=inf;
        if(f){
            for(int i=1;i<=3;i++)
            ans=min(ans,dp[n+1][i]);
                printf("OK %d\n",ans);
        }
       // for(int i=1;i<=n+1;i++,printf("\n"))
      //      for(int j=1;j<=3;j++)
        //        printf("%d ",dp[i][j]);

    }
    return 0;
}
