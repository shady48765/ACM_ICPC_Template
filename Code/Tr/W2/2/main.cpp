#include <cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
typedef long long LL;
long long SG(LL x)
{
    if(x%2)
        return SG(x/2);
    else return x/2;
}
int main()
{
    int T;
    scanf("%d",&T);
    int n;
    LL x;
    while(T--)
    {
        LL sg=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
        scanf("%lld",&x);
        sg^=SG(x);
        }
        if(sg==0) printf("NO\n");
        else printf("YES\n");
    }
    return 0;
}
