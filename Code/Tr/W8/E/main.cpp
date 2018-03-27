#include <iostream>
#include<cstdio>
using namespace std;
long long res[40];
int main()
{
    int n;
    res[0]=1;
    for(int i=1;i<=30;i++)
        for(int j=0;j<i;j++)
            res[i]+=res[i-j-1]*res[j];
    while(scanf("%d",&n)&&n)
    {
        printf("%lld\n",res[n]);
    }
    return 0;
}
