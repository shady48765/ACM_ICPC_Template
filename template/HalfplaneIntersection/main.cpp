#include <cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const double eps=1e-9;
struct point
{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y){}
};
typedef point Vector;
Vector operator-(point A,point B)
{
    return Vector(A.x-B.x,A.y-B.y);
}
struct line
{
    point P;
    Vector v;
    double ang;
    line(){}
    line(point P,Vector v):P(P),v(v){ang=atan2(v.y,v.x);}
    bool operator<(const line& L) const
    {
        return ang<L.ang;
    }
};
double cross(Vector A,Vector B)
{
    return A.x*B.y-A.y*B.x;
}
bool Onleft(line L,point P)
{
    return cross(L.v,P-L.P)>0;
}
point inter(line a,line b)
{
    Vector u=a.P-b.P;
    double t=cross(b.v,u)/cross(a.v,b.v);
    return point(a.P.x+t*a.v.x,a.P.y+t*a.v.y);
}
int HalfPlaneIntersection(line* L,int n,point* poly)
{
    sort(L,L+n);
    int first,last;
    point *p=new point[n];
    line *q=new line[n];
    q[first=last=0]=L[0];
    for(int i=1;i<n;i++)
    {
        while(first<last&&!Onleft(L[i],p[last-1])) last--;
        while(first<last&&!Onleft(L[i],p[first])) first++;
        q[++last]=L[i];
        if(fabs(cross(q[last].v,q[last-1].v))<eps){
            last--;
            if(Onleft(q[last],L[i].P)) q[last]=L[i];
        }
        if(first<last) p[last-1]=inter(q[last-1],q[last]);
    }
    while(first<last&&!Onleft(q[first],p[last-1])) last--;
    if(last-first<=1) return 0;
    p[last]=inter(q[last],q[first]);
    int m=0;
    for(int i=first;i<=last;i++) poly[m++]=p[i];
    return m;
}
int main()
{

    return 0;
}
