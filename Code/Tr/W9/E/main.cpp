#include <cstdio>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<iostream>
#include<map>
#include<set>
#include<vector>
using namespace std;
map<string,int> mp;
string S,s1;
int cnt=0;
vector<int> G[1010];
bool vis[1010];
void  dfs(int u)
{
    vis[u]=true;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(!vis[v]) dfs(v);
    }
}
int main()
{
    //freopen("data.in","r",stdin);
    int n;
    while(cin>>n&&n)
    {
        memset(G,0,sizeof(G));
        mp.clear();cnt=0;
        memset(vis,false,sizeof(vis));
        for(int i=1;i<=n;i++)
        {
            int j;
            cin>>S;s1.clear();
            for(j=0;;j++)
            if(S[j]==':') break;
            else
            s1.push_back(S[j]);

            if(!mp[s1]) mp[s1]=++cnt;
            int now=mp[s1];
            s1.clear();
            for(j=j+1;j<S.size();j++)
            {
                if(S[j]==','||S[j]=='.')
                {
                    if(!mp[s1]) mp[s1]=++cnt;
                    G[now].push_back(mp[s1]);
            //cout<<s1<<endl;
                    s1.clear();
                }
                else
                    s1.push_back(S[j]);
            }
        }
        dfs(1);
        int cnt=0;
        for(int i=2;i<=1005;i++)
            if(vis[i]&&G[i].size()==0) cnt++;
        cout<<cnt<<endl;
    }
    return 0;
}
