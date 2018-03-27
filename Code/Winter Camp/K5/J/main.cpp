#include <iostream>
#include <algorithm>
#define P 1000000007
using namespace std;
int n,a[500],sum[500];
int f[310][90100],g[310][90100];
long long  ans,V;
int main()
{
    cin>>n;
    for (int i=1;i<=n;i++){
        cin>>a[i];
        sum[i]=sum[i-1]+a[i];
    }
    cin>>V;
    f[0][0]=1;
    for (int i=0;i<=V+1;i++) g[0][i]=1;
    for (int i=1;i<=n;i++){
        for (int j=1;j<=V+1;j++)
            {
            if (j-a[i]-1<0) f[i][j]=g[i-1][j]; else
            f[i][j]=g[i-1][j]-g[i-1][j-a[i]-1];
            cout<<i<<" "<<j<<" "<<f[i][j]<<endl;
        }
        for (int j=1;j<=sum[i+1];j++){
            g[i][j]=g[i][j-1]+f[i][j];
            cout<<i<<" "<<j<<" "<<g[i][j]<<endl;
        }
    }
    ans=1;
    for (int i=1;i<=n;i++){
        ans=ans*i%P;
    }
    cout<<ans<<endl;
    cout<<"< "<<g[n][V]<<endl;
    cout<<"= "<<f[n][V+1]<<endl;
    ans=ans*g[n][V]%P;
    ans=(ans+f[n][V+1])%P;
    cout<<ans<<endl;
    return 0;
}
