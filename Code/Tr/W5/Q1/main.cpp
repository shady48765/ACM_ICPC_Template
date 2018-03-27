#include <cstdio>
#include<algorithm>
using namespace std;
int A[250005],n;
int main()
{
    while(scanf("%d",&n)&&n)
    {
        for(int i=1;i<=n;i++) scanf("%d",&A[i]);
        A[0]=0;
        for(int i=1;i<=n;i++) A[i]+=A[i-1];
        int mi=0,res=-99999;
        for(int i=1;i<=n;i++)
        {
            res=max(A[i]-mi,res);
            mi=min(A[i],mi);
        }
        printf("%d\n",res);
    }
    return 0;
}
