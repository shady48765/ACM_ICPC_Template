#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int maz[4040][4040],n,k;
int dp[808][4040];
int res[808][4040];
int cost(int i,int j)
{
    int res=maz[j][j]-maz[j][i-1]-maz[i-1][j]+maz[i-1][i-1];
    return res/2;
}
inline int read(int &t) {
    int f = 1;char c;
    while (c = getchar(), c < '0' || c > '9') if (c == '-') f = -1;
    t = c - '0';
    while (c = getchar(), c >= '0' && c <= '9') t = t * 10 + c - '0';
    t *= f;
}
void calc(int d,int l,int r,int lb,int hb)
{
    if(l>r) return;
    if(l==r)
    {
        int low=res[d][l-1];
        for(int j=lb;j<=hb;j++)
        {
            if(dp[d][l]>dp[d-1][j]+cost(j+1,l))
            {
                dp[d][l]=dp[d-1][j]+cost(j+1,l);
                res[d][l]=j;
            }
        }
    }
    else
    {
        int mid=(l+r)>>1;
        for(int j=lb;j<=hb;j++)
        {
            if(dp[d][mid]>dp[d-1][j]+cost(j+1,mid))
            {
                dp[d][mid]=dp[d-1][j]+cost(j+1,mid);
                res[d][mid]=j;
            }
        }
        calc(d,l,mid-1,lb,mid-2);
        calc(d,mid+1,r,res[d][mid],hb);
    }
}
int main()
{
    read(n);read(k);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            read(maz[i][j]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            maz[i][j]+=maz[i][j-1]+maz[i-1][j]-maz[i-1][j-1];
    memset(dp,0x3f,sizeof(dp));
    for(int i=1;i<=n;i++)
        dp[1][i]=cost(1,i),res[1][i]=i;
    for(int i=2;i<=k;i++)
        dp[i][i]=dp[i-1][i-1]+cost(i,i),res[i][i]=i-1;
    for(int i=2;i<=k;i++)
        calc(i,i,n,i-1,n-1);
    printf("%d",dp[k][n]);
    return 0;
}
