#include <cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
const int maxn=100010;
int num,n,m,x,y;
int u[202000],v[202000],next[202000],top[202000];
int d[202000][2],c[202000],res[202000];
int vis[202000];
double f[202000];
void add(int x,int y){
    ++num;u[num]=x;v[num]=y;next[num]=top[x];top[x]=num;
    ++num;u[num]=y;v[num]=x;next[num]=top[y];top[y]=num;
}
void bfs(int s,int k){
    queue<int> q;
    memset(vis,0,sizeof(vis));
    q.push(s);vis[s]=1;
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for (int i=top[x];i;i=next[i]){
            if (!vis[v[i]]){
                d[v[i]][k]=d[x][k]+1;
                q.push(v[i]);
                vis[v[i]]=1;
            }
        }
    }
}
void bfs(int x){
    queue<int> q;
    memset(vis,0,sizeof(vis));
    q.push(x);vis[x]=1;
    while (!q.empty()){
        x=q.front();
        q.pop();
        if (x!=n) f[x]=f[x]+(double)m/c[x];
        cout<<x<<" "<<f[x]<<" "<<c[x]<<endl;
        for (int i=top[x];i;i=next[i]) if (res[v[i]]==1 && f[v[i]]<f[x]){
                cout<<x<<" "<<f[x]<<" "<<v[i]<<" "<<f[v[i]]<<endl;
            if (f[v[i]]>f[x]){
                f[v[i]]=f[x];
                c[v[i]]=1;
            }else if (fabs(f[v[i]]-f[x])<0.000000001){
                c[v[i]]++;
            }
            vis[v[i]]=1;
            q.push(v[i]);
        }
    }
}
int main()
{
 //   cout<<1e8<<endl;
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        add(x,y);
    }
    bfs(1,0);
    bfs(n,1);
    for (int i=1;i<=n;i++){
        if (d[i][0]+d[i][1]==d[n][0]) res[i]=1;
        if (i!=n) f[i]=1000000000.0;
    }
    for (int i=1;i<=n;i++){
        printf("%d %d %d %d\n",i,d[i][0],d[i][1],res[i]);
    }

    bfs(n);
    printf("%.9lf\n",f[1]);
    return 0;
}
