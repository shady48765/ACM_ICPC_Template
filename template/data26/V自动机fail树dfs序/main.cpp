#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cstring>
#include<vector>
#include <queue>
using namespace std;
const int maxn=300010;
//vector<int> G[maxn];
int N;
struct Edge
{
    int v, next;
    Edge(){}
    Edge(int v, int next):v(v), next(next){}
} edge[maxn<<1];
int head[maxn],edge_cnt;
void init_edge()
{
    memset(head, -1, sizeof(head));
    edge_cnt = 0;
}
void add_edge(int u, int v)
{
    edge[edge_cnt] = Edge(v, head[u]);
    head[u] = edge_cnt++;
}
struct Trie
{
    int next[maxn][26],fail[maxn];
    int root,tot;
    int newnode()
    {
        for(int i = 0;i < 26;i++)
            next[tot][i] = -1;
        return tot++;
    }
    void init()
    {
        tot = 0;
        root = newnode();
    }
    void insert(char buf[],int i)
    {
        int len = strlen(buf);
        int now = root;
        for(int i = 0;i < len;i++)
        {
            if(next[now][buf[i]-'a'] == -1)
                next[now][buf[i]-'a'] = newnode();
            now = next[now][buf[i]-'a'];
        }
    }
    void build()
    {
        queue<int>Q;
        fail[root] = root;
        for(int i = 0;i < 26;i++)
            if(next[root][i] == -1)
                next[root][i] = root;
            else
            {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        while( !Q.empty() )
        {

            int now = Q.front();
            Q.pop();
            for(int i = 0;i < 26;i++)
                if(next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else
                {
                    fail[next[now][i]]=next[fail[now]][i];
                    Q.push(next[now][i]);
                }
        }
    }
    void build_fail_tree()
    {
        //for(int i=0;i<tot;i++) G[i].clear();
        init_edge();
        for(int i=1;i<tot;i++)
        {
            //G[i].push_back(fail[i]);
            //G[fail[i]].push_back(i);
            add_edge(i,fail[i]);
            add_edge(fail[i],i);
        }
        N=tot;
    }
}ac;
int weight[maxn],pos[maxn],temp;
char buf[maxn];
int L[maxn],R[maxn],dfn;
void dfs(int u,int fa)
{
    L[u]=++dfn;
    /*for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(v==fa) continue;
        dfs(v,u);
    }*/
    for (int i = head[u]; i != -1; i = edge[i].next)
    {
        int v = edge[i].v;
        if(v==fa) continue;
        dfs(v, u);
    }
    R[u]=dfn;
}
int mx[maxn<<2];
void update(int o,int l,int r,int ql,int qr,int v)
{
    if(ql<=l&&r<=qr)
    {
        mx[o]=max(mx[o],v);
    }
    else
    {
        int mid=(l+r)>>1;
        if(ql<=mid)
            update(o<<1,l,mid,ql,qr,v);
        if(qr>mid)
            update(o<<1|1,mid+1,r,ql,qr,v);
    }
}
int res;
void query(int o,int l,int r,int p)
{
    if(l==r)
    {
        res=max(res,mx[o]);
        return ;
    }
    else
    {
        int mid=(l+r)>>1;
        res=max(res,mx[o]);
        if(p<=mid)
            query(o<<1,l,mid,p);
        if(p>mid)
            query(o<<1|1,mid+1,r,p);
    }
}
int main()
{
    //freopen("data.in","r",stdin);
    int T,n,kase=0;
    scanf("%d",&T);
    while(T--)
    {
        ac.init();
        scanf("%d",&n);
        temp=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%s%d",buf+temp,&weight[i]);
            int len=strlen(buf+temp);
            ac.insert(buf+temp,i);
            temp+=len;
            pos[i]=temp;
        }
        ac.build();
        ac.build_fail_tree();
        dfn=0;
        dfs(0,-1);
        memset(mx,0,sizeof(mx));
        int ans=0;
        int j=0;
        for(int i=1;i<=n;i++)
        {
            int now=0;
            temp=0;
            while(j<pos[i])
            {
                now=ac.next[now][buf[j]-'a'];
                res=0;
                query(1,1,N,L[now]);
                temp=max(temp,res+weight[i]);
                j++;
            }
            ans=max(ans,temp);
            update(1,1,N,L[now],R[now],temp);
        }
        printf("Case #%d: %d\n",++kase,ans);
    }
    return 0;
}
