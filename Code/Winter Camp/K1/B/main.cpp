#include <iostream>
#include<vector>
#include<cstring>
#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int mod=1000000007;
int A[44];
long long B[44],C[44];
long long mp[44][44][2][2];
vector<int> G[44];
vector<int> g[2];
bool vis[44];
map<int,int> tab;
void dfs(int u,int d)
{
    if(vis[u]) return;
    vis[u]=true;
    g[d].push_back(u);
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(vis[v]) continue;
        dfs(v,d^1);
    }
}
int main()
{
    //freopen("data.in","r",stdin);
    int n,m,a,b;
    long long t1,t2,t3,t4;
    memset(vis,false,sizeof(vis));
    cin>>n>>m;
    for(int i=1;i<=m;i++)
    {
        cin>>a>>b>>t1>>t2>>t3>>t4;
        mp[a][b][0][0]=t1;
        mp[a][b][0][1]=t2;
        mp[a][b][1][0]=t3;
        mp[a][b][1][1]=t4;

        mp[b][a][0][0]=t1;
        mp[b][a][0][1]=t3;
        mp[b][a][1][0]=t2;
        mp[b][a][1][1]=t4;

        G[a].push_back(b);
        G[b].push_back(a);
    }
    for(int i=1;i<=n;i++) if(!vis[i])
        dfs(i,0);
    if(g[0].size()>g[1].size()) swap(g[0],g[1]);
    int two=g[0].size();
    for(int i=0;i<g[1].size();i++) tab[g[1][i]]=i;
    long long ans=0;
    for(int S=0;S<(1<<two);S++)
    {
      //  cout<<S<<"****"<<two<<endl;
        for(int i=0;i<two;i++)
        if(S&(1<<i)) A[i]=1;else A[i]=0;
     //   for(int i=0;i<two;i++)
    //    //    cout<<A[i]<<" #";
    //    cout<<endl;
        for(int i=0;i<g[1].size();i++)
            B[i]=C[i]=1;
        for(int i=0;i<g[0].size();i++)
        {
            int u=g[0][i];
            //cout<<u<<"@@@@@"<<endl;
            for(int j=0;j<G[u].size();j++)
            {
                int v=G[u][j];
                B[tab[v]]*=mp[u][v][A[i]][0];
                B[tab[v]]%=mod;

              //  cout<<mp[u][v][A[i]][0]<<" "<<u<<" "<<v<<" "<<A[i]<<endl;
             //   cout<<mp[u][v][A[i]][1]<<" "<<u<<" "<<v<<" "<<A[i]<<endl;
                C[tab[v]]*=mp[u][v][A[i]][1];
                C[tab[v]]%=mod;
                //cout<<B[tab[v]]<<"=____________="<<C[tab[v]]<<endl;
            }
        }
        long long tp=1;
        for(int i=0;i<g[1].size();i++)
            tp=tp*(B[i]+C[i])%mod;
        //cout<<tp<<"   tp res"<<endl;
        tp%=mod;
        ans+=tp;
        ans%=mod;
    }
    cout<<ans<<endl;
    return 0;
}
