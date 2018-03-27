#include <cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<set>
#include<cstring>

using namespace std;
char maz[105][105];
int hsh[105][105];
int len[10006];
int dp[10005];
int cnt;
bool ext[10005];
set<int> tp;
set<int> ::iterator it;
vector<int> fa[10006],son[10006];
bool check(int u)
{
    for(int i=0;i<fa[u].size();i++)
    {
        int v=fa[u][i];
        if(ext[v]) return false;
    }
    return true;
}
int DP(int u)
{
   // printf("### %d\n",u);
    if(!ext[u]) return 0;
    if(dp[u]!=-1) return dp[u];
    ext[u]=false;
    dp[u]=len[u];
   // printf("%d\n",dp[u]);
    for(int i=0;i<son[u].size();i++)
    {
        if(check(son[u][i])) dp[u]+=DP(son[u][i]);
    }
    return dp[u];
}
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)&&(n+m))
    {
        for(int i=1;i<=n;i++) scanf("%s",maz[i]+1);
        cnt=0;
        memset(dp,-1,sizeof(dp));
        memset(fa,0,sizeof(fa));
        memset(son,0,sizeof(son));
        memset(len,0,sizeof(len));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;)
            {
                int t=maz[i][j]-'0';
                if(t==0) hsh[i][j]=0,j+=1;
                else
                {
                    ++cnt;
                    for(int k=j;k<=j+t-1;k++)
                        hsh[i][k]=cnt;
                    len[cnt]=t;
                    j+=t;
                }
            }
        for(int i=1;i<=n-1;i++)
            for(int j=1;j<=m;)
            {
                int t=maz[i][j]-'0';
                if(t==0) {j+=1;continue;}
                else
                {
                    tp.clear();
                    for(int k=j;k<=j+t-1;k++)
                        if(hsh[i+1][k]!=0) tp.insert(hsh[i+1][k]);
                    for(it=tp.begin();it!=tp.end();++it)
                        fa[hsh[i][j]].push_back(*it),son[*it].push_back(hsh[i][j]);
                    j+=t;
                }
            }
            int ans=0;
        for(int i=cnt;i>=1;i--){memset(ext,true,sizeof(ext)); ans=max(ans,DP(i));//printf("\n");
        }
        printf("%d\n",ans);
    }
    return 0;
}
