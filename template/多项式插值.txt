#include <iostream>
#include<algorithm>
#define Rep(i,b) for(int i=1;i<=b;i++)
using namespace std;
typedef long long Int;
const int mod=10007;
const int MaxN=33;
Int x[MaxN+10],y[MaxN+10];
Int f(int n)
{
    int res=0;
    Rep(i,n)Rep(j,n)Rep(k,n)Rep(l,n)Rep(m,n)
        res+=abs(abs(i-j)*abs(j-k)*abs(k-l)*abs(l-m)*abs(m-i)),res%=mod;
    return res;
}
Int FastPow(int base,int n)
{
    Int res=1;
    while(n){
        if(n&1){
            res*=base;
            res%=mod;
        }
        base=base*base%mod;
        n>>=1;
    }
    return res;
}
Int Inv(int n)
{
    return FastPow(n,mod-2);
}
Int Phi(int X,int i)
{
    Int res=1;
    Rep(j,MaxN)
     if(j==i) continue;
     else res=res*(X-x[j])%mod,res=res*Inv(x[i]-x[j])%mod;
    return res;
}
Int g(int x)
{
    Int res=0;
    Rep(i,MaxN) res+=y[i]*Phi(x,i)%mod,res%=mod;
    return (res+mod)%mod;
}
int main()
{
    Rep(i,MaxN) x[i]=i,y[i]=f(i);
    int n;
    while(cin>>n)
    {
        if(n==0) break;
        cout<<g(n)<<endl;
    }
    return 0;
}
