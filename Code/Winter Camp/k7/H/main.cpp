#include <iostream>
#define p 1000000007
using namespace std;
long long ans1,ans2,ans3,tan[100100],two[100100];
int main()
{
    int n;
    cin>>n;
    tan[0]=1;
     for (int i=1;i<=n+2;i++){
        tan[i]=tan[i-1]*i;
        tan[i]%=p;
    }
    two[0]=1;
    for (int i=1;i<=10000;i++){
        two[i]=two[i-1]*2;
        two[i]%=p;
    }
    if (n==1)
    {
        ans1=1;
    }
    else
    {
        ans1=two[(n-2)*(n-1)/2];
        ans1%=p;
        ans1*=tan[n];
        ans1%=p;
    }
    if (n==1)
    {
        ans2=0;
    }
    else if (n==2)
    {
        ans2=1;
    }
    else if (n==3)
    {
        ans2=6;
    }
    else
    {
        ans2=two[(n-4)*(n+1)/2];
        ans2%=p;
        ans2*=tan[n+1];
        ans2%=p;
    }
    if (n==1)
    {
        ans3=0;
    }
    else if(n==2)
    {
        ans3=0;
    }
    else if(n==3)
    {
        ans3=6;
    }
    else
    {
        ans3=two[(n-4)*(n+1)/2];
        ans3%=p;
        ans3*=tan[n];
        ans3%=p;
        ans3*=n;
        ans3%=p;
    }
    cout<<ans1<<endl;
    cout<<ans2<<endl;
    cout<<ans3<<endl;
    return 0;
}
