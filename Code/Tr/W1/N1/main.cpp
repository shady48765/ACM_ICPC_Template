#include <cstdio>
#include<algorithm>
#include<cstring>
#include<map>
using namespace std;
int A[100005],cnt[100005];
int main()
{
    menset(cnt,0,sizeof(cnt));
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&A[i]);
    sort(A+1,A+1+n);
    if(A[n]-A[1]>n/2||n%2)
    {
         printf("NO");
         return 0;
    }
    for(int i=1;i<=n;i++) cnt[A[i]-A[1]+1]++;
    int tru = 0;
    for(int i=1;i<=a[n]-a[1];i++){
         int t = f[i]-tru;
         if(i==a[n-1]-a[0]){
              if(t==0)
              printf("YES");
              else printf("NO");
              return 0;
         }
         if(t<=0){
              printf("NO");
              return 0;
         }
         tru = t;
    }
}
