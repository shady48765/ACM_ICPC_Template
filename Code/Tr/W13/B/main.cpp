#include <cstdio>
#include<map>
#include<algorithm>
#include<vector>
using namespace std;
char op[5];
int x,y,n,mx,my,tx=0,ty=0;
struct _node
{
    int x,y,t;
}node[500005];
map<int,int> tree[500005];
//vector<int> Gx,Gy;
int Gx[500005],Gy[500005];
void Hash()
{
    //sort(Gx.begin(),Gx.end());
    //sort(Gy.begin(),Gy.end());
    //Gx.erase(unique(Gx.begin(),Gx.end()),Gx.end());
    //Gy.erase(unique(Gy.begin(),Gy.end()),Gy.end());
    sort(Gx,Gx+tx);
    sort(Gy,Gy+ty);
    mx=unique(Gx,Gx+tx)-Gx;
    my=unique(Gy,Gy+ty)-Gy;
    for(int i=1;i<=n;i++)
    {
        node[i].x=(lower_bound(Gx,Gx+mx,node[i].x)-Gx+1);
        node[i].y=(lower_bound(Gy,Gy+my,node[i].y)-Gy+1);
    }
   // mx=Gx.size();my=Gy.size();
}
int main()
{
    //freopen("data.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%s%d%d",op,&node[i].x,&node[i].y);
        node[i].t=(*op=='+');
        //Gx.push_back(node[i].x);
       // Gy.push_back(node[i].y);
       Gx[tx++]=node[i].x;
       Gy[ty++]=node[i].y;
    }
    Hash();
    for(int i=1;i<=n;i++)
    {
        if(node[i].t==1)
        {
            for(int x=node[i].x;x<=mx;x+=(x&-x))
                for(int y=node[i].y;y>0;y-=(y&-y))
                    tree[x][y]++;
        }
        else
        {
            int res=0;
            for(int x=node[i].x;x>0;x-=(x&-x))
                for(int y=node[i].y;y<=my;y+=(y&-y))
                    res+=tree[x][y];
            printf("%d\n",res);
        }
    }
    return 0;
}
