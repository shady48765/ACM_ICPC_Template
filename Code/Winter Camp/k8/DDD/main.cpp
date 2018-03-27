#include <cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int A[2020];
int dp[2020][2020];
int main()
{
    int T,n;
    //n=2000;
    //for(int i=1;i<=n;i++) A[i]=(n+1-i)*10000;
    //T=10;
    scanf("%d",&T);
    while(T--)
    {
        //memset(dp,0,sizeof(dp));
        scanf("%d",&n);
        int res=0;
        if(n==1) res=1;
        for(int i=1;i<=n;i++) scanf("%d",&A[i]);
        sort(A+1,A+1+n);
        for(int i=2;i<=n;i++)
        {
            int k=i-2;
            for(int j=i-1;j>=1;j--)
            {
                int d=A[i]-A[j];
                while(A[j]-A[k]<d&&k>0) k--;
                if(k==0)
                {
                    dp[i][j]=2,res=max(res,2);
                }
                else
                {
                    if(A[j]-A[k]==d) dp[i][j]=dp[j][k]+1,res=max(dp[i][j],res);
                    else dp[i][j]=2,res=max(res,2);
                }
            }
        }
        printf("%d\n",res);
    }
    return 0;
}
