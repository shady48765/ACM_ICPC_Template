#include <iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cstring>
using namespace std;
int n,A,B,u,v;
vector<int> G[300010];
int res[300010];
int dmax=0,root,maxlen=0;
int depth[300010],mx[300010],temp[300010];
bool flag=false;
void dfs(int u,int fa,int d)
{
    if(d>=dmax) dmax=d,root=u;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa) continue;
        dfs(v,u,d+1);
    }
}
void dfs2(int u,int fa,int d)
{
    if(d>maxlen) maxlen=d;
    depth[u]=d;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa) continue;
        dfs2(v,u,d+1);
        mx[u]=max(mx[v]+1,mx[u]);
    }
}
void dfs3(int u,int fa)
{
    //printf("@@@ %d %d %d %d\n",u,mx[u],depth[u],maxlen);
    if(mx[u]+depth[u]==maxlen&&(mx[u]-depth[u]==0||mx[u]-depth[u]==1||depth[u]-mx[u]==1))
    {

        flag=true;
        root=u;

        //printf("root is now %d",root);
    }
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa) continue;
        dfs3(v,u);
    }
}
void dfs4(int u,int fa,int d)
{
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa) continue;
        dfs4(v,u,d+1);
        mx[u]=min(mx[v]+1,mx[u]);
    }
}
void dfs5(int u,int fa)
{
   // printf("%d\n",u);
    if(fa!=-1)
    {
        vector<int> temp; temp.clear();
        for(int i=0;i<G[u].size();i++) if(G[u][i]!=fa)
            temp.push_back(-mx[G[u][i]]-1);
        sort(temp.begin(),temp.end());
        for(int i=0;i<temp.size();i++)
        {
            res[-temp[i]]=max(res[-temp[i]],i+2);
        }
    }
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa) continue;
        dfs5(v,u);
    }
}
void debug(int u,int fa)
{
    printf("### %d %d\n",u,mx[u]);
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa) continue;
        debug(v,u);
    }
}
int main()
{
    //freopen("data.in","r",stdin);
    freopen("amoeba.in","r",stdin);
    freopen("amoeba.out","w",stdout);
    scanf("%d%d%d",&n,&A,&B);
    for(int i=1;i<=n-1;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,-1,0);
    dfs2(root,-1,0);
    dfs3(1,-1);
    //printf("root %d\n",root);
    res[maxlen]=1;
    memset(mx,0,sizeof(mx));
    dfs2(root,-1,0);
   // dfs4(root,-1,0);
    dfs5(root,-1);
   // debug(root,-1);
    vector<int> temp; temp.clear();
    for(int i=0;i<G[root].size();i++)
        temp.push_back(-mx[G[root][i]]-1);
    sort(temp.begin(),temp.end());
    for(int i=0;i<temp.size();i++)
    {
        res[-temp[i]]=max(res[-temp[i]],i+1);
    }

    int tp=res[B];
    //printf("root is %d\n",root);

    for(int i=maxlen;i>=A;i--)
    {
        res[i]=max(tp,res[i]);
        tp=max(tp,res[i]);
    }

    for(int i=A;i<=B;i++)
        printf("%d\n",res[i]);
    return 0;
}
