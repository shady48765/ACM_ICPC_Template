#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#define maxn 200010
#define low 31

using namespace std;

int cut[low+2][maxn];
int bit[low+2][maxn];
int c[low+2][maxn];
int sum[low+2];
int t[low+2];
int a[maxn];
int n,m;

int main()
{
    scanf("%d%d",&n,&m);
    memset(t,0,sizeof(t));
    for (int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        for (int j=low;j>=0;j--)
            bit[j][i]=(a[i]>>j)&1;
        cut[low+1][i]=i;
    }
    //for (int i=low;i>=0;i--)
    //{

    //    for (int j=1;j<=n;j++)
    //    {
    //        cout<<bit[i][j]<<' ';
    //    }
    //    cout<<endl;
    //}
    //cout<<endl;
    sum[low+1]=n;
    for (int i=low;i>=0;i--)
    {
        for (int j=1;j<=sum[i+1];j++)
        {
            c[i][j]=0;
            for (int k=cut[i+1][j-1]+1;k<=cut[i+1][j];k++) c[i][j]=c[i][j]^bit[i][k];
        }
        //cout<<endl;
        //cout<<"c[i][j]:  ";
        //for (int j=1;j<=sum[i+1];j++) printf("%d ",c[i][j]);
        //cout<<endl;
        int now=0;
        sum[i]=0;
        for (int j=1;j<=sum[i+1];j++)
        {
            if (c[i][j]==0&&now==0) cut[i][++sum[i]]=cut[i+1][j];
            if (c[i][j]==1)
            {
                if (now==0) now=1;
                else if (now==1) cut[i][++sum[i]]=cut[i+1][j],now=0;
            }
        }

        //cout<<"cut:  ";
        //for (int k=1;k<=sum[i];k++) cout<<cut[i][k]<<' ';
        //cout<<endl;
        if (sum[i]>=m && cut[i][sum[i]]==n) t[i]=0;
        else
        {
            t[i]=1;
            sum[i]=sum[i+1];
            for (int k=1;k<=sum[i+1];k++) cut[i][k]=cut[i+1][k];
        }
        //cout<<"cut:  ";
        //for (int k=1;k<=sum[i];k++) cout<<cut[i][k]<<' ';
        //cout<<endl;
    }
    //for (int i=low;i>=0;i--) cout<<t[i]<<' ';
    //cout<<endl;
    int ans=0;
    for (int i=low;i>=0;i--)
        if (t[i]==1)
            ans+=(1<<i);
    printf("%d\n",ans);
    return 0;
}
