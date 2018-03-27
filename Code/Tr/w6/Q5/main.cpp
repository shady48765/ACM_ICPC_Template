#include <iostream>
#include <queue>
#include<cstring>
#include<vector>
#include<cstdio>
using namespace std;
#define inf 0x7fffffff
#define M 20000

struct edge{
    int v, w, next;
}e[M];
bool inq[M];
int dist[M], pre[M], n, cnt, ind[M];

void init ()
{
    memset (pre, -1, sizeof(pre)); cnt = 0;
}
void addedge (int u, int v, int w)
{
    e[cnt].v = v; e[cnt].w = w; e[cnt].next = pre[u]; pre[u] = cnt++;
}
bool spfa ()
{
    int i, v, w,u;
    queue<int> q;
    for (i =1; i <= n; i++)
    {
        dist[i] = 0;
        inq[i] = true;
        ind[i] = 0;
        q.push (i);
    }
    while (!q.empty())
    {
        u = q.front();
        if (++ind[u] > n)
            return false;
        q.pop();
        inq[u] = false;
        for (i = pre[u]; i != -1; i = e[i].next)
        {
            v = e[i].v;
            w = e[i].w;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                if (!inq[v])
                {
                    q.push (v);
                    inq[v] = true;
                }
            }
        }
    }
	return true;
}
char buff[200];
vector<int> tp;
int main()
{
    while(scanf("%d",&n)&&n)
    {
        init();int m;
        scanf("%d",&m);
        getchar();

        for(int i=1;i<=m;i++)
        {
            gets(buff);
            int len=strlen(buff);
            int type=0;
            tp.clear();
            for(int i=0,j=0;i<len;i++)
            {
                if(j==3)
                {
                    if(buff[i]=='a') type=1;
                    else if(buff[i]=='w') type=2;
                    break;
                }
                if(buff[i]==' ') j++;
            }
            for(int i=0;i<len;i++)
            {
                if(buff[i]<='9'&&buff[i]>='0')
                {
                    int ttp=0;
                    while(buff[i]<='9'&&buff[i]>='0')
                    {
                        ttp*=10;
                        ttp+=(buff[i]-'0');
                        i++;
                    }
                    tp.push_back(ttp);
                }
            }
            if(type==2)
            {
                addedge(tp[2],tp[0],tp[1]);
                addedge(tp[0],tp[2],0);
            }
            else if(type==1)
            {
                addedge(tp[0],tp[2],-tp[1]);
            }
        }
        if(!spfa())
            printf("Impossible.\n");
        else
        {
            int base=9999999;
            for(int i=1;i<=n;i++)
                base=min(base,dist[i]);
            for(int i=1;i<=n;i++)
                printf("%d ",dist[i]-base+1);
                printf("\n");
        }

    }


    return 0;
}
