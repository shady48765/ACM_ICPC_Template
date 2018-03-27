#include <cstdio>
#include<map>
using namespace std;
int A[100005],N,S,W;
long long B[100005],Q;
map<long long ,int> mp;
void init()
{
    int g=S;
    for(int i=0;i<N;i++)
    {
        A[i]=(g/7)%10;
        if(g%2==0)
            g/=2;
        else
            g=(g/2)^W;
    }
}
int main()
{
    //freopen("data.in","r",stdin);
    while(scanf("%d%d%d%lld",&N,&S,&W,&Q)&&(N+S+W+Q))
    {
        init();
        mp.clear();
        long long base=1;
        long long res=0;
        int tp;
        long long sum=0;
        if(Q==5||Q==2)
        {
            int tt1=0;
            for(int i=0;i<N;i++)
            {
                if(A[i]!=0) tt1++;
                if(A[i]%Q==0) res+=tt1;
            }
                printf("%d\n",res);
                continue;
        }
        for(int i=N-1;i>=0;i--)
        {
            B[i]=(base*(long long)A[i]+sum)%Q;
            tp=++mp[B[i]];
            if(A[i]!=0)
                res+=(tp-1);
            if(A[i]!=0&&B[i]==0)
                res+=1;
            base=base*10%Q;
            sum=B[i];
            //printf("### %lld\n",res);
        }
       // for(int i=0;i<N;i++)
       //     printf("%lld ",B[i]);
      //  printf("\n");
        printf("%lld\n",res);
    }
    return 0;
}
