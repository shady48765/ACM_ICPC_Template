#include <cstdio>
#include<algorithm>
using namespace std;
int A[50],n;
bool check()
{
    for(int i=2;i<=n;i++)
        if(A[i]!=A[i-1]) return false;
    return true;
}
int main()
{
    int kase=0;
    while(scanf("%d",&n))
    {
        if(n==0) break;
        ++kase;
        for(int i=1;i<=n;i++) scanf("%d",&A[i]);
        int cnt=0;
        while(!check())
        {
            ++cnt;
            int tp=A[1];
            for(int i=1;i<=n-1;i++)
                A[i]=abs(A[i+1]-A[i]);
            A[n]=abs(A[n]-tp);
            if(cnt>1000)
                break;
        }
        if(cnt<=1000)
            printf("Case %d: %d iterations\n",kase,cnt);
        else
            printf("Case %d: not attained\n",kase);
    }
    return 0;
}
