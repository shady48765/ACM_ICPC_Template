#include <iostream>
#include<cstdio>
using namespace std;

int main()
{
    freopen("group.in","r",stdin);
    int n,m;
    scanf("%d%d",&n,&m);
    int maxx;
    if(m%2==0)
        maxx=m/2*3;
    else maxx=m/2*3+1;
    printf("%d %d",n-m,maxx+3*(n-m-1));
    return 0;
}
