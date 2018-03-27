#include <cstdio>

using namespace std;
char maz[20][20];
//B 1 C 10 D 100
int ts(char x)
{
    if(x=='B') return 1;
    if(x=='C') return 2;
    if(x=='D') return 4;
    else return 0;
}
char it(int x)
{
    if(x==1) return 'B';
    if(x==2) return 'C';
    if(x==3) return 'D';
}
bool put(int x,int y)
{
    int color=0;
    if(maz[x][y]=='.'&&maz[x+1][y]=='.'&&maz[x+1][y-1]=='.'&&maz[x+1][y+1]=='.'&&maz[x+2][y]=='.') ;
    else return false;
    color|=ts(maz[x-1][y]);
    color|=ts(maz[x+3][y]);
    color|=ts(maz[x][y+1]);
    color|=ts(maz[x][y-1]);
    color|=ts(maz[x+1][y+2]);
    color|=ts(maz[x+1][y-2]);
    color|=ts(maz[x+2][y+1]);
    color|=ts(maz[x+2][y-1]);
    //printf("color %d\n",color);
    int c=-1;
    if((color&1)==0) c=1;
    else if((color&2)==0) c=2;
    else if((color&4)==0) c=3;
    if(c==-1) return false;
    maz[x][y]=maz[x+1][y]=maz[x+1][y-1]=maz[x+1][y+1]=maz[x+2][y]=it(c);
    return true;
}
bool dfs()
int main()
{
    //freopen("data.in","r",stdin);
    int T,n;
    scanf("%d",&T);
    for(int kase=1;kase<=T;kase++)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%s",maz[i]+1);
        bool ok=true;
        for(int i=1;i<=n-2;i++)
            for(int j=2;j<=n-1;j++)
            if(maz[i][j]=='.') {ok=put(i,j);}
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                if(maz[i][j]=='.') ok=false;
        printf("Case %d:",kase);
        if(ok){
            printf("\n");
            for(int i=1;i<=n;i++)
            printf("%s\n",maz[i]+1);
        }
        else printf(" Not Possible!\n");
    }
    return 0;
}
