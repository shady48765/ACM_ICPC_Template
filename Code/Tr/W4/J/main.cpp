#include <iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct point
{
    int x,y;
    int v,l;
    int no;
    point(int x=0,int y=0):x(x),y(y) {}
    bool operator < (const point& a) const
    {
        return x<a.x||(x==a.x&&y<a.y);
    }
}P[105],poly[105],O;
typedef point Vector;
Vector operator-(point A,point B)
{
    return Vector(B.x-A.x,B.y-A.y);
}
int cross(Vector a,Vector b) {return a.x*b.y-a.y*b.x;}
Vector operator*(int x,Vector A)
{
    return Vector(A.x*x,A.y*x);
}
Vector operator+(Vector A,Vector B)
{
    return Vector(A.x+B.x,A.y+B.y);
}
int main()
{
    int n;
    O=point(0,0);
    int kase=0;
    while(scanf("%d",&n)&&n)
    {
        ++kase;
        int xx,yy;
        for(int i=0;i<n;i++)
        {
            scanf("%d%d",&xx,&yy);
            P[i]=point(xx,yy);
        }
        Vector res=Vector(0,0);
        int under=0;
        for(int i=0;i<n;i++)
        {
            under+=cross(P[i]-O,P[(i+1)%n]-O);
            Vector tp=(P[i]-O)+(P[(i+1)%n]-O);
            res=res+cross(P[i]-O,P[(i+1)%n]-O)*tp;
        }
        double resx=res.x/-3.0/(under*1.0);
        double resy=res.y/-3.0/(under*1.0);
        printf("Stage #%d: %.6lf %.6lf\n",kase,resx,resy);
    }
    return 0;
}
