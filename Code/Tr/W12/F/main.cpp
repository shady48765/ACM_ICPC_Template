#include <cstdio>
#include<algorithm>
using namespace std;
int x,y;
int main()
{
    int n;
   // freopen("knights.in","r",stdin);
  // freopen("knights.out","w",stdout);
    while(scanf("%d",&n)&&n)
    {
        int f=1;
        bool ok=false;
        int now=1000000000,t,t1,t2;
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d",&x,&y);
            if(y==0) ok=true;
            t=min(x/3,y/3);
            t1=x-3*t,t2=y-3*t;
            if(t<now)
            {
                now=t;
                if(t1<2) f=2;
                else f=1;
            }
            else if(t==now)
            {
                if(t1<2) f=2;
            }
        }
        if(ok) f=2;
        if(f==1)
            printf("Andrew wins the game\n");
        else
            printf("Peter wins the game\n");

    }
    return 0;
}
