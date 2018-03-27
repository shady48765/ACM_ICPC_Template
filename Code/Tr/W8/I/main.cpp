#include <cstdio>
#include<cstring>
#include<vector>
using namespace std;
const int maxn=150005;
int n,k,fa,root;
int val[maxn];
vector<int> G[maxn];
int tp[305];
int dfs(int u)
{
    int cur[305];
    int max_now=0,max_son;
    memset(cur,-1,sizeof(cur));
    memset(tp,-1,sizeof(tp));
    cur[0]=tp[0]=0;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        max_son=dfs(v);
        for(int i=max_now;i>=0;i--)
            for(int j=1;j<=max_son;j++)
                if(i+j>k) break;
            else
            {
                cur[i+j]=max(cur[i+j],cur[i]+tp[j]);
            }
        max_now+=max_son;
        max_now=min(max_now,k);
    }
    if(G[u].size()==0)
    {
        tp[1]=val[u];
        return 1;
    }
    for(int i=0;i<=max_now;i++)
        tp[i]=cur[i];
    tp[1]=max(tp[1],val[u]);
    return max_now;
}
int main()
{
    while(scanf("%d%d",&n,&k)!=EOF)
    {
        for(int i=0;i<=n;i++) G[i].clear();
        memset(tp,0,sizeof(tp));

        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&fa,&val[i]);
            if(fa)
                G[fa].push_back(i);
            else
                root=i;
        }
        dfs(root);
        if(tp[k]==-1)
            printf("impossible\n");
        else
            printf("%d\n",tp[k]);
    }
    return 0;
}
