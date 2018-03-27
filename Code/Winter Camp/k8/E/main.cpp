#include <iostream>
#include <cstdio>
using namespace std;
int n,tail,ans;
int a[2001000],q[2001000],f[2001000];
int main()
{
    int tt;cin>>tt;
    while (tt--){
        scanf("%d",&n);
        for (int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        f[1]=1;
        q[tail=1]=1;
        for (int i=2;i<=n;i++){
            f[i]=n+1;
            while (a[q[tail]]<=a[i] && tail>0) {
                f[i]=min(f[i],f[q[tail]]+1);
                tail--;
            }
            q[++tail]=i;
        }
        ans=n+1;
        for (int i=1;i<=tail;i++){
            ans=min(ans,f[q[i]]);
        }
        printf("%d\n",ans);
    }
    return 0;
}
