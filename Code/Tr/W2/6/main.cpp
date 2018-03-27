#include <cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;
const int dx[4]={-1,1,0,0};
const int dy[4]={0,0,-1,1};
int L,H,W,n,S;
int dp[10010];
char maz[104][104][104];

struct Man
{
    int l,h,w,v,t;
    Man(){}
    Man(int l,int h,int w,int v):l(l),h(h),w(w),v(v){t=0;}
};
struct point
{
    int x,y,f,step;
    point(){}
    point(int f,int x,int y,int step):f(f),x(x),y(y),step(step){}
}st,now,nxt;
vector<Man> man;
void init()
{
    man.clear();
    int l,h,w,v;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d%d%d",&l,&h,&w,&v);
        man.push_back(Man(l,h,w,v));
        maz[l][h][w]='Q';
    }
    for(int i=1;i<=H;i++)
        for(int j=1;j<=W;j++)
            if(maz[1][i][j]=='S')
                st=point(1,i,j,0);
}
bool vis[104][104][104];
void bfs()
{
    memset(vis,false,sizeof(vis));
    queue<point> q;
    q.push(st);
    int x,y,f,s;
    int nx,ny,nf,ns;
    while(!q.empty())
    {
        now=q.front();q.pop();
        f=now.f;x=now.x,y=now.y;s=now.step;
        vis[f][x][y]=true;
        //printf("to  %d %d %d %d \n",f,x,y,s);
        if(maz[f][x][y]=='Q')
        {
            for(int i=0;i<man.size();i++)
                if(man[i].l==f&&man[i].h==x&&man[i].w==y)
                {
                    man[i].t=3*s;break;
                }
        }
        bool ok=true;
        if(maz[f][x][y]=='U')
        {
            nf=f+1;
            if(nf>L||nf<1) ok=false;
            if(maz[nf][x][y]=='X') ok=false;
            if(vis[nf][x][y]) ok=false;
            if(ok)q.push(point(nf,x,y,s+1));
        }
        else if(maz[f][x][y]=='D')
        {
            nf=f-1;
            if(nf>L||nf<1) ok=false;
            if(maz[nf][x][y]=='X') ok=false;
            if(vis[nf][x][y]) ok=false;
            if(ok)q.push(point(nf,x,y,s+1));
        }
        for(int i=0;i<4;i++)
        {
            nx=x+dx[i];
            ny=y+dy[i];
            if(nx>H||nx<1||ny>W||ny<1) continue;
            if(maz[f][nx][ny]=='X') continue;
            nf=f;
            ns=s+1;
            if(vis[nf][nx][ny]) continue;
            q.push(point(nf,nx,ny,ns));
        }
    }
}
int main()
{
    freopen("data.in","r",stdin);
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d%d",&L,&H,&W,&n,&S);
        for(int i=1;i<=L;i++)
            for(int x=1;x<=H;x++)
                scanf("%s",maz[i][x]+1);
        init();

        //for(int i=1;i<=L;i++)
        //    for(int x=1;x<=H;x++)
          //      printf("%s\n",maz[i][x]+1);
        bfs();
        //for(int i=0;i<man.size();i++)
          //  printf("#%d %d %d %d   %d\n",man[i].l,man[i].h,man[i].w,man[i].v,man[i].t);
         memset(dp,0,sizeof(dp));
         for(int i=0;i<man.size();i++)
            for(int ss=S;ss-man[i].t>=0;ss--)
         {
             dp[ss]=max(dp[ss],dp[ss-man[i].t]+man[i].v);
         }
         printf("%d\n",dp[S]);
    }

}
