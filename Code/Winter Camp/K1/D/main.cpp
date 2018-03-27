#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
int x_1,x_2,x_3,y_1,y_2,y_3;
double dist(double x_1,double y_1,double x_2,double y_2){
    return (sqrt((x_1-x_2)*(x_1-x_2)+(y_1-y_2)*(y_1-y_2)));
}
int main()
{

    cin>>x_1>>y_1;
    cin>>x_2>>y_2;
    cin>>x_3>>y_3;

    double ans=dist(x_1,y_1,x_3,y_3)+dist(x_2,y_2,x_3,y_3)*2;
    printf("%.9lf\n",ans);
    return 0;
}

