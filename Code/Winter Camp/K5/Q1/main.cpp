#include <iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<cstring>
#include<cmath>
using namespace std;
double d;
int main()
{
    scanf("%lf",&d);
    if(d<=sqrt(2.0)&&d>=1.000)
        printf("%.12f",max(2.000,d*sqrt(2.0)));
    else if(d<=sqrt(5)&&d>=2.000)
        printf("%.12f",max(3.000,d*sqrt(2.0)));
    else printf("%.12f",d*sqrt(2.0));
    return 0;
}
