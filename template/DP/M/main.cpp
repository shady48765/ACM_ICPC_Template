#include <iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
const double eps=1e-8;
double p1,p2,p3,p4;
int n,m,k;
double dp[2010][2010];
double temp[2020];
int main()
{
    while(scanf("%d%d%d%lf%lf%lf%lf",&n,&m,&k,&p1,&p2,&p3,&p4)!=EOF)
    {
        if(p4<eps)
        {
            puts("0.00000");
            continue;
        }
        dp[1][1]=p4/(1-p1-p2);
        p2=p2/(1-p1);
        p3=p3/(1-p1);
        p4=p4/(1-p1);
        for(int i=2;i<=n;i++)
        {
            for(int j=2;j<=min(i,k);j++)
                temp[j]=dp[i-1][j-1]*p3+p4;
            for(int j=k+1;j<=i;j++)
                temp[j]=dp[i-1][j-1]*p3;
            double p=p2,tem=p4;
            for(int j=2;j<=i;j++)
            {
                tem*=p2;
                tem+=temp[j];
                p*=p2;
            }
            dp[i][i]=tem/(1-p);
            dp[i][1]=dp[i][i]*p2+p4;
            for(int j=2;j<=i;j++)
                dp[i][j]=dp[i][j-1]*p2+temp[j];
        }
        printf("%.5f\n",dp[n][m]);
    }
    return 0;
}
