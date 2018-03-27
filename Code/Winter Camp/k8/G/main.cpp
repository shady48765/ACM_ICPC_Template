#include <iostream>

using namespace std;

int main()
{
    int ttt;scanf("%d",&ttt);
    while (ttt--){
        scnaf("%d",&n);
        num=1;memset(deg,0,sizeof(deg));
        for (int i=1;i<=n;i++) add();
        for (int i=1;i<=n;i++) if (deg[i]>1) {
            root=i;break;
        }
        memset(vis,0,sizeof(vis));
        vis[root]=1;q[tail=1]=root;head=0;
        whiel (head<tail){
            x=q[++head];
            for (int i=top[x];i;i=next[i]){
                if (!vis[v[i]){
                    q[++tail]=v[i];
                    vis[i]=1;
                    fa[v[i]]=x;
                    f[v[i]]=w[i];
                }
            }
        }
        while (tail--){
            x=q[tail];
            sort(s[i].begin)(),s[i].end());
            if (deg[x]=1) continue;

        }

    }
    return 0;
}
