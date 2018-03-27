#include <cstdio>
#include<algorithm>
using namespace std;
int A[100010];
int n,k,x,y,T;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d%d%d",&n,&k,&x,&y);
        for(int i=1;i<=n;i++) scanf("%d",&A[i]);
        for(int i=1;i<=n;i++) A[i]=-A[i];
        sort(A+1,A+1+n);
        for(int i=1;i<=n;i++) A[i]=-A[i];
        bool ok=true;
        if(n<k+2)
            ok=false;
        else
        if(x>y)
        {
            if(A[1]>=x&&A[2]>=x)
            {
                for(int i=3;i<=k+2;i++)
                    if(A[i]<y) ok=false;
            }
            else ok=false;
        }
        else
        {
            for(int i=1;i<=k;i++) if(A[i]<y) ok=false;
            if(A[k+1]<x||A[k+2]<x) ok=false;
        }
        if(ok) printf("YES\n");
        else printf("NO\n");
    }

    return 0;
}
