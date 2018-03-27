#include <cstdio>
#include<algorithm>
#include<queue>
#include<vector>
#include<cmath>
#include<iostream>
using namespace std;
const double pi2=atan(1.0)*8.0;
const double pi=atan(1.0)*4.0;
int n,k;
double a;
struct Ang
{
    double d;
    int id;
    Ang(){}
    Ang(double d,int id):d(d),id(id){}
    bool operator<(const Ang& rhs) const
    {
        return d<rhs.d;
    }
};
vector<Ang> A;
double get(int i)
{
    int l,r;
    double lag,rag;
    if(i-1==-1)
    {
        l=n-1;lag=A[i].d+pi2-A[l].d;
    }
    else {l=i-1;lag=A[i].d-A[l].d;}

    if(i+1==n)
    {
        r=0;lag=A[r].d+pi2-A[i].d;
    }
    else {r=i+1;rag=A[r].d-A[i].d;}
    cout<<lag<<" "<<rag<<endl;
    if(lag>=pi||rag>=pi) return 99;
    else
    {
        return sin(lag)+sin(rag)-sin(lag+rag);
    }
}
int main()
{
    freopen("post.in","r",stdin);
    scanf("%d%d",&n,&k);A.clear();
    for(int i=1;i<=n;i++)
    {
        scanf("%lf",&a); A.push_back(Ang(a,i));
    }
    sort(A.begin(),A.end());
    double mini;
    int pos;
    while(n>k)
    {
        mini=9999;
        for(int i=0;i<n;i++)
        {
            double tp=get(i);
            if(tp<mini) pos=i,mini=tp;
        }
        for(int i=pos;i<n-1;i++) A[i]=A[i+1];
        n--;
    }
    for(int i=0;i<k;i++)
        printf("%d ",A[i].id);
    return 0;
}
