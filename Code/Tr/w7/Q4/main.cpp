#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int MAXN = 100050;
const int MAXM = 300010;

struct Edge
{
    int to,next;
}edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN];
int Index,top;
bool Instack[MAXN];
bool cut[MAXN];
int add_block[MAXN];
void addedge(int u,int v)
{
    edge[tot].to = v;edge[tot].next = head[u];head[u] = tot++;
}
int subindex;
void Tarjan(int u,int pre)
{
    int v;
    DFN[u] = Low[u] = ++Index;
    Stack[top++] = u;
    Instack[u] = true;
    int son = 0;
    for(int i = head[u];i != -1;i = edge[i].next)
    {
        v = edge[i].to;
        if(v == pre)continue;
        if(v == subindex)continue;
        if(!DFN[v])
        {
            son++;
            Tarjan(v,u);
            if(Low[u] > Low[v])Low[u] = Low[v];
            if(u != pre && Low[v] >= DFN[u])
            {
                cut[u] = true;
                add_block[u]++;
            }
        }
        else if(Instack[v] && Low[u] > DFN[v])
            Low[u] = DFN[v];
    }
    if(u == pre && son > 1)cut[u] = true;
    if(u == pre )add_block[u] = son - 1;
    Instack[u] = false;
    top--;
}
void init()
{
    tot = 0;
    memset(head,-1,sizeof(head));
    memset(cut,false,sizeof(cut));
}
void bfs()
{
    ;
}
int main()
{
    //freopen("assassination.in","r",stdin);
    int n,m,s,t;
    init();
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1;i<=m;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        addedge(u,v);
        //addedge(v,u);
    }
    Tarjan(s,-1);
    int aa=0;
    for(int i=1;i<=n;i++)
        if(cut[i]&&i!=s&&i!=t) ++aa;
        printf("%d\n",aa);
    for(int i=1;i<=n;i++)
        if(cut[i]&&i!=s&&i!=t) printf("%d ",i);
    return 0;
}
