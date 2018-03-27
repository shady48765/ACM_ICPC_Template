#include <stdlib.h>
#include <string.h>
// trojsojusz.cpp
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
long double calc(long double x,long double y,long double z) {
  long double from=0,to=min(x,y),middle,a,b,c,z2;
  for (int f=0; f<100; f++) {
    a=(from+to)/2;
    b=(sqrt(4*x*x-3*a*a)-a)/2;
    c=(sqrt(4*y*y-3*a*a)-a)/2;    
    z2=b*b+c*c+b*c;
    if (z2<z*z) to=a; else from=a;
  }
  a=to;
  b=(sqrt(4*x*x-3*a*a)-a)/2;
  c=(sqrt(4*y*y-3*a*a)-a)/2;    
//  printf("%.6lf\n",(double)(a+b+c));
  return min(min(a+b+c,x+y),min(x+z,y+z));
}

long double sqr(long double x) { return x*x; }
int main() {
  int x[3],y[3],z[3];
  long double d[3];
  for (int i=0; i<3; i++) scanf("%d %d %d",&x[i],&y[i],&z[i]);
  for (int i=0; i<3; i++)
    d[i]=sqrt(sqr(x[i]-x[(i+1)%3])+sqr(y[i]-y[(i+1)%3])+sqr(z[i]-z[(i+1)%3]));
  printf("%.6lf\n",(double)calc(d[0],d[1],d[2]));
  return 0;
}
