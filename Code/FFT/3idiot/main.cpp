#include <iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
const double pi=4*atan(1.0);
const int N=100004;
struct Complex
{
    double re,im;
    Complex(double re=0,double im=0):re(re),im(im){}
    Complex operator* (Complex rhs){return Complex(re*rhs.re-im*rhs.im,re*rhs.im+im*rhs.re);}
    Complex operator+ (Complex rhs){return Complex(re+rhs.re,im+rhs.im);}
    Complex operator- (Complex rhs){return Complex(re-rhs.re,im-rhs.im);}
};
void FFT(Complex f[],int len,int on)
{
    for(int i=1,j=len/2;i<len-1;i++)
    {
        if(i<j) swap(f[i],f[j]);
        int k=len/2;
        while(j>=k)
        {
            j-=k;k>>=1;
        }
        if(j<k) j+=k;
    }
    for(int i=2;i<=len;i<<=1)
    {
        Complex wn(cos(-on*2*pi/i),sin(-on*2*pi/i));
        for(int j=0;j<len;j+=i)
        {
            Complex w(1,0);
            for(int k=j;k<j+i/2;k++)
            {
                Complex u=f[k],t=w*f[k+i/2];
                f[k]=u+t;
                f[k+i/2]=u-t;
                w=w*wn;
            }
        }
    }
    if(on==-1)
    for(int i=0;i<len;i++)
    f[i].re/=len;
}
Complex f1[6*N];
int A[3*N],n,T;
long long Num[6*N];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        int Max=0;
        for(int i=1;i<=n;i++) scanf("%d",&A[i]),Max=max(A[i],Max);
        int len=1;
        Max++;
        while(len<2*Max) len<<=1;
        memset(f1,0,len*sizeof(f1[0]));
        //memset(f1,0,sizeof(f1));
        for(int i=1;i<=n;i++)
        {
            f1[A[i]].re+=1;
        }
        FFT(f1,len,1);
        for(int i=0;i<len;i++) f1[i]=f1[i]*f1[i];
        FFT(f1,len,-1);
        for(int i=1;i<=n;i++) f1[A[i]*2].re-=1;
        Num[0]=0;
        for(int i=1;i<len;i++) Num[i]=(long long)floor(f1[i].re+0.5)/2+Num[i-1];
        sort(A+1,A+n+1);
        long long res=0;
        for(int i=1;i<=n;i++)
        {
            res+=Num[len-1]-Num[A[i]];
            res-=1LL*(i-1)*(n-i);
            res-=1LL*(n-1-i)*(n-i)/2;
            res-=n-1;
        }
        long long bottom=1LL*n*(n-1)*(n-2)/6;
        printf("%.7f\n",1.0*res/bottom);
    }

    return 0;
}
