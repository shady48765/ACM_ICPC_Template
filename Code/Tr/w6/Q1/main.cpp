#include<cstring>
#include<cstdio>
using namespace std;
int n1,n2;
int A[2010],B[2010],C[4020];
int dp[1050][1050];
bool dfs(int a,int b,int c)
{
    if(c==(n1+n2+1)) return true;
    if(dp[a][b]!=-1) return dp[a][b];
    if(a<=n1&&A[a]==C[c])
        if(dfs(a+1,b,c+1)) return dp[a][b]=1;
    if(b<=n2&&B[b]==C[c])
        if(dfs(a,b+1,c+1)) return dp[a][b]=1;
    return dp[a][b]=0;
}
int main()
{
    while(scanf("%d%d",&n1,&n2)&&(n1+n2))
    {
        memset(dp,-1,sizeof(dp));
        for(int i=1;i<=n1;i++) scanf("%d",&A[i]);
        for(int i=1;i<=n2;i++) scanf("%d",&B[i]);
        for(int i=1;i<=n1+n2;i++) scanf("%d",&C[i]);
        if(dfs(1,1,1)) printf("possible\n");
        else printf("not possible\n");
    }

    return 0;
}
