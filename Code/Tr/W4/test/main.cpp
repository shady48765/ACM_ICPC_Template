#include<iostream>
#include<cstdio>
#include<cstring>
#include<set>
#include <cmath>
#include<algorithm>
using namespace std;
const int L=111;
const double eps=0.0;
struct point
{
	double x,y;
}p[L];

void G(int n,int q)//重心
{
	int i,j,t;
	double sx=0,sy=0;
	double area=0,num;
	point temp;
	for(i=0;i<n-1;i++)
		{
			num=(p[i].x*p[i+1].y-p[i+1].x*p[i].y);
			sx+=(p[i+1].x+p[i].x)*num;
			sy+=(p[i+1].y+p[i].y)*num;
			area+=num/2;
		}
        num=p[n-1].x*p[0].y-p[0].x*p[n-1].y;
        sx+=(p[n-1].x+p[0].x)*num;
        sy+=(p[n-1].y+p[0].y)*num;
        area+=num/2;
		//MAX=area;//其实这也是面积啊。
		temp.x=sx/(6*area);
		temp.y=sy/(6*area);
	printf("Stage #%d: %.6lf %.6lf\n",q,temp.x,temp.y);
}
int main()
{
    int i,j,n,q=1;
    while(~scanf("%d",&n)&&n)
    {
        for(i=0;i<n;i++)
            scanf("%lf %lf",&p[i].x,&p[i].y);
        G(n,q);
        q++;
    }
    return 0;
}
