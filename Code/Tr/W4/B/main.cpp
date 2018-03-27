#include <cstdio>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;
int maz[105][105];
vector<int> G[10006];
bool used[10006];
int deg[10006];
int now[10006];
int color[10005];
int ver[10006];
int main()
{
    int n,m;
    while(scanf("%d%d",&n,&m)&&(n+m))
    {
        memset(color,0,sizeof(color));
        priority_queue<int,vector<int>,greater<int> > q;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",&maz[i][j]),color[maz[i][j]]=1;
        memset(G,0,sizeof(G));
        memset(now,0,sizeof(now));
        memset(used,0,sizeof(used));
        memset(ver,0,sizeof(ver));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
        {
            if(now[maz[i][j]]==0) now[maz[i][j]]=i;
            else
            {
                if(now[maz[i][j]]==i) ver[maz[i][j]]=-1;
                else ver[maz[i][j]]=1;
                used[maz[i][j]]=1;
            }
        }
        for(int i=1;i<=10004;i++) if(now[i]!=0&&!used[i]) {q.push(i);color[i]=0;}
        memset(used,0,sizeof(used));
        memset(now,0,sizeof(now));
        memset(deg,0,sizeof(deg));
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
        {
            if(!used[maz[i][j]]&&color[i])
            {
                if(ver[maz[i][j]]==1)
                for(int k=1;k<=n;k++)
                {
                    if(maz[k][j]==maz[i][j]) continue;
                    G[maz[i][j]].push_back(maz[k][j]);
                    deg[maz[k][j]]++;
                }
                else if(ver[maz[i][j]]==-1)
                for(int k=1;k<=m;k++)
                {
                    if(maz[i][k]==maz[i][j]) continue;
                    G[maz[i][j]].push_back(maz[i][k]);
                    deg[maz[i][k]]++;
                }
                used[maz[i][j]]=true;
            }
        }
        while(!q.empty())
        {
            int x=q.top();q.pop();
            printf("%d ",x);
        }
        for(int i=1;i<=10000;i++) if(color[i]&&deg[i]==0) q.push(i);

        while(!q.empty())
        {
            int x=q.top();q.pop();
            printf("%d ",x);
            for(int i=0;i<G[x].size();i++)
            {
                deg[G[x][i]]--;
                if(deg[G[x][i]]==0) q.push(G[x][i]);
            }
        }
        printf("\n");
    }
    return 0;
}

