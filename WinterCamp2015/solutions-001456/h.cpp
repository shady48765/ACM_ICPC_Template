#include <stdlib.h>
#include <string.h>
#include<cstdio>
#include<vector>
#include<algorithm>
#define FOREACH(i,c) for(__typeof((c).begin()) i =(c).begin();i!=(c).end();i++)
using namespace std;
const int MAXN = 1507;
vector<int> graf [MAXN];
vector<int> type [MAXN];
bool vis[MAXN];
int match[MAXN];
int match_type[MAXN];
int n,m,matches;
bool dfs(int v)
{
    vis[v]=true;
    FOREACH(i,graf[v])
    {
        if(match[*i]==-1 || (!vis[match[*i]] && dfs(match[*i])))
        {
            match[*i]=v;
            match[v]=*i;
            match_type[v]=match_type[*i] = type[v][i-graf[v].begin()];
            return true;
        }
    }
    return false;
}
bool stage(int n)
{
    for(int i=0;i<n;i++)
        vis[i]=false;
    bool res = false;
    for(int i=0;i<n;i++)
        if(match[i]== -1 && !vis[i])
            if(dfs(i))
            {
                res=true;
                matches++;
            }
    return res;
}
vector<pair<double, double > > spots;
void create_edges(int x, int y)
{
    FOREACH(i,spots)
    {
        int nx = 2*i->first-x-1;
        int ny = 2*i->second-y-1;
        if(0 <= nx && nx < m && 0<=ny && ny <n)
        {
            graf[n*x+y].push_back(n*nx+ny);
            type[n*x+y].push_back(i-spots.begin()+1);
        }
    }
}

int main()
{
    int z;
    scanf("%d",&z);
    while(z--)
    {
        scanf("%d %d",&m,&n);
        for(int i=0;i<n*m;i++)
        {
            match[i]=-1;
            graf[i].clear();
            type[i].clear();
        }
        spots.clear();
        int k;

        scanf("%d",&k);
        for(int i=0;i<k;i++)
        {
            pair<double, double> tmp;
            scanf("%lf %lf",&tmp.first,&tmp.second);
            spots.push_back(tmp);
        }

        matches=0;
        for(int i=0;i<m;i++)
            for(int j=0;j<n;j++)
                create_edges(i,j);
        while(stage(n*m));
        if((m*n)%2==0 && matches == (n*m)/2)
        {
            printf("YES\n");
            for(int i=0;i<m;i++)
            {
                for(int j=0;j<n;j++)
                    printf("%d ",match_type[i*n+j]);
                printf("\n");
            }
        }
        else
            printf("NO\n");
    }
}
