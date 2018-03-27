#include <cstdio>
#include<algorithm>
using namespace std;
int A[100];
int main()
{
    int n;
    while(1){
    scanf("%d",&n);
    for(int i=1;i<=n;i++) A[i]=i;
    int cnt=0;
    do
    {
        bool ok=true;
        for(int i=1;i<=n&&ok;i++)
            for(int j=i+1;j<=n&&ok;j++)
                for(int k=j+1;k<=n&&ok;k++)
                    if(A[i]<A[j]&&A[j]<A[k]) ok=false;
        if(ok) cnt++;
    }while(next_permutation(A+1,A+1+n));
    printf("n=%d %d\n",n,cnt);
    }
    return 0;
}
