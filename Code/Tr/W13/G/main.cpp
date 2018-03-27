#include <cstdio>
#include<cstring>
using namespace std;
const unsigned long long base=1331;
unsigned long long Z[50005],H1[50005],H2[50005];
char S1[50005],S2[50005];
void init()
{
    int n=strlen(S1+1);
    H1[n+1]=0;
    for(int i=n;i>=1;i--)
    {
        H1[i]=H1[i+1]*base+S1[i];
    }
    n=strlen(S2+1);
    H2[n+1]=0;
    for(int i=n;i>=1;i--)
    {
        H2[i]=H2[i+1]*base+S2[i];
    }
}
unsigned long long gethash1(int st,int ed)
{
    return H1[st]-H1[ed+1]*Z[ed-st+1];
}
unsigned long long gethash2(int st,int ed)
{
    return H2[st]-H2[ed+1]*Z[ed-st+1];
}
int main()
{
    Z[0]=1;
    for(int i=1;i<=50000;i++)
        Z[i]=Z[i-1]*base;
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%s%s",S1+1,S2+1);
        init();
        int n1=strlen(S1+1);
        int n2=strlen(S2+1);
        int ans=1;
        for(int i=1;i<=n2&&i<=n1;i++)
        {
            if(gethash2(1,i)==gethash1(n1-i+1,n1)) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}
