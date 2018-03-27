#include <iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
using namespace std;
int T,n;
int A[505];
int dp[2][9000];
int S=1<<13;
int lowbit(int x)
{
    return x&(-x);
}
int calc(int s,int x)
{
    if(s&x)
        return calc(s^x,x<<1)+(x<<1);
    else
        return 0;
}
int main()
{
    //freopen("data.in","r",stdin);
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&A[i]);
        memset(dp,-1,sizeof(dp));
        int now=0;
        dp[0][0]=0;
        for(int i=1;i<=n;i++)
        {
            now^=1;
            memset(dp[now],-1,sizeof(dp[now]));
            for(int s=0;s<S;s++)if(dp[now^1][s]!=-1)
            {

                if(lowbit(s)>=A[i])
                {
                    dp[now][s+A[i]]=max(dp[now][s+A[i]],dp[now^1][s]+calc(s,A[i])+A[i]);
                }
                else
                    dp[now][A[i]]=max(dp[now][A[i]],dp[now^1][s]+A[i]);
            }
            for(int s=0;s<S;s++)
                dp[now][s]=max(dp[now][s],dp[now^1][s]);
        }
        int res=0;
        for(int s=0;s<S;s++)
            res=max(res,dp[now][s]);
        printf("%d\n",res);
    }
    return 0;
}
