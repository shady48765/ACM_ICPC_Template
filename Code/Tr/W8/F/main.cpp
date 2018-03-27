#include <cstdio>
#include<queue>
#include<cstring>
using namespace std;
int step[1010][1010][4];
long long dp[1010][1010][4];
int n,m,r1,c1,r2,c2,d1;
long long mod;
char dir[2];
const int dx[4]={-1,0,1,0};
const int dy[4]={0,1,0,-1};//N E S W
char maz[1010][1010];
struct state
{
    int x,y,d,s;
    state(){}
    state(int x,int y,int d,int s):x(x),y(y),d(d),s(s){}
    bool operator<(const state& t) const
    {
        return d>t.d;
    }
};
bool valid(state tt)
{
    if(tt.x<=n&&tt.x>=1&&tt.y<=m&&tt.y>=1&&maz[tt.x][tt.y]!='*') return true;
    else return false;
}
void bfs()
{
    memset(step,-1,sizeof(step));
    step[r1][c1][d1]=1;
    //priority_queue<state> q;
    queue<state> q;
    q.push(state(r1,c1,d1,1));
    state now,news;
    while(!q.empty())
    {
        //now=q.top();q.pop();
        now=q.front();q.pop();
        if(step[now.x][now.y][now.d]!=-1&&step[now.x][now.y][now.d]<now.s) continue;
        //printf("%d %d %d %d\n",now.x,now.y,now.d,now.s);
        news=state(now.x+dx[now.d],now.y+dy[now.d],now.d,now.s+1);
        if(valid(news))
        {
            if(step[news.x][news.y][news.d]==-1||step[news.x][news.y][news.d]>news.s){
                step[news.x][news.y][news.d]=news.s;
                q.push(news);
            }
        }
        news=state(now.x,now.y,(now.d+1)%4,now.s+1);
        if(valid(news))
        if(step[news.x][news.y][news.d]==-1||step[news.x][news.y][news.d]>news.s){
                step[news.x][news.y][news.d]=news.s;
                q.push(news);
            }
        news=state(now.x,now.y,(now.d+3)%4,now.s+1);
        if(valid(news))
        if(step[news.x][news.y][news.d]==-1||step[news.x][news.y][news.d]>news.s){
                step[news.x][news.y][news.d]=news.s;
                q.push(news);
            }
    }
}
long long DP(int x,int y,int d)
{
    if(dp[x][y][d]!=-1)
        return dp[x][y][d];
    long long res=0;
    if(step[x][y][(d+1)%4]+1==step[x][y][d])
        res+=DP(x,y,(d+1)%4);
    res%=mod;
    if(step[x][y][(d+3)%4]+1==step[x][y][d])
        res+=DP(x,y,(d+3)%4);
    res%=mod;
    if(step[x-dx[d]][y-dy[d]][d]+1==step[x][y][d]){
        if(x-dx[d]>=1&&x-dx[d]<=n&&y-dy[d]<=m&&y-dy[d]>=1&&maz[x-dx[d]][y-dy[d]]!='*')
            res+=DP(x-dx[d],y-dy[d],d);
    }
    res%=mod;
    return dp[x][y][d]=res;
}
int main()
{
    //freopen("data.in","r",stdin);
    int kase=0;
    while(scanf("%d%d%I64d",&n,&m,&mod)!=EOF){
            if(mod==0 )break;
            ++kase;
        for(int i=1;i<=n;i++) scanf("%s",maz[i]+1);
        scanf("%d%d%d%d%s",&r1,&c1,&r2,&c2,dir);
        r1++,c1++,r2++,c2++;//N E S W
        if(dir[0]=='N') d1=0;
        else if(dir[0]=='E') d1=1;
        else if(dir[0]=='S') d1=2;
        else if(dir[0]=='W') d1=3;
        bfs();
        memset(dp,-1,sizeof(dp));
        dp[r1][c1][d1]=1;
        int mini=99999999;
        for(int i=0;i<4;i++)
            mini=min(mini,step[r2][c2][i]);
        long long res=0;
        if(mini!=-1)
        for(int i=0;i<4;i++)
            if(step[r2][c2][i]==mini)
            {
                res+=DP(r2,c2,i),res%=mod;
            }
        printf("Case %d: %I64d ",kase,mod);
        if(mini==-1)
            printf("-1\n");
        else
            printf("%I64d\n",res);
    }
    return 0;
}
