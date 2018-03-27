#include <iostream>
#include<cstdio>
using namespace std;
int calc(long long x)
{
    int  ct=0;
    while(x)
    {
        if(x%10==0) ct++;
        x/=10;
    }
    return ct;
}
int main()
{
    int k,p;
    scanf("%d%d",&k,&p);
    long long base=1;
    while(k--) base*=10;
    long long  re=0;
    for(long long  i=1;i<=base;i++)
        re+=calc(i);
    printf("%lld",re);
    return 0;
}
