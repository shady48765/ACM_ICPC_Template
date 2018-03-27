#include <iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
typedef long long LL;
const int maxn=100010;
LL dist[maxn<<1],t[maxn],sum[maxn];
LL dp[105][maxn];
LL q[maxn];
int n,m,p,x;
int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for(int i=2;i<=n;i++)
    {
        scanf("%I64d",&dist[i]);
        dist[i]+=dist[i-1];
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%I64d",&x,&t[i]);
        t[i]-=dist[x];
    }
    sort(t+1,t+1+m);
    for(int i=1;i<=m;i++) sum[i]=t[i]+sum[i-1];
    for(int i=1;i<=m;i++) dp[1][i]=t[i]*i-sum[i];
    for(int i=2;i<=p;i++)
    {
        q[0]=0;
        int head=0,tail=0;
        for(int j=1;j<=m;j++)
        {
            while (head<tail && ((dp[i-1][q[head+1]]+sum[q[head+1]]) - (dp[i-1][q[head]]+sum[q[head]]) < (q[head+1] - q[head])*t[j])) head++;
            dp[i][j] = dp[i-1][q[head]] + (j-q[head])*t[j] - (sum[j]-sum[q[head]]);
            q[++tail]=j;
            while (head < tail-1 && ((dp[i-1][q[tail]]+sum[q[tail]])-(dp[i-1][q[tail-1]]+sum[q[tail-1]]))*(q[tail-1]-q[tail-2]) < ((dp[i-1][q[tail-1]]+sum[q[tail-1]])-(dp[i-1][q[tail-2]]+sum[q[tail-2]]))*(q[tail]-q[tail-1]))
                --tail,q[tail] = q[tail+1];
        }
    }
    printf("%I64d\n",dp[p][m]);
    return 0;
}
