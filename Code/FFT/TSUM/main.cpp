#include <iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstring>
using namespace std;
const double pi=4*atan(1.0);
const int N=140050;
const int base=20000;
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
Complex A[N],B[N],C[N],D[N];
int n,x;
int main()
{
    //freopen("data.in","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        x+=base;
        A[x].re+=1;
        D[x].re+=1;
        B[2*x].re+=1;
        C[3*x].re+=1;
    }
    int len=1;
    while(len<6*base) len<<=1;
    FFT(D,len,1);
    FFT(A,len,1);
    FFT(B,len,1);
    for(int i=0;i<len;i++)
    {
        A[i]=A[i]*D[i];
        A[i]=A[i]*D[i];
        B[i]=B[i]*D[i];
    }
    FFT(A,len,-1);
    FFT(B,len,-1);
    for(int i=0;i<len;i++){
        long long x=0LL+floor(A[i].re+0.5)-3*floor(B[i].re+0.5)+2*floor(C[i].re+0.5);
        x/=6;
        if(x>0)
            printf("%d : %lld\n",i-3*base,x);
    }
    return 0;
}
