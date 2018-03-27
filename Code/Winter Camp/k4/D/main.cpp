#include <iostream>
#include <cstdio>
using namespace std;
int f[202000];
int x,y;
char ch[2];
int ans;
int main()
{
    int n,r;
    cin>>n;
    for (int i=1;i<=n;i++) f[i]=-1;
    f[0]=0;
    for (int i=1;i<=n;i++){
        scanf("%s%d%d",ch,&x,&y);
        if (ch[0]=='B') x=i-1-x,y=i-1-y;
        if (f[x]!=-1 && 0<=x && x<=i-1 ) f[x+1]=max(f[x+1],f[x]+1);
        if (f[x]!=-1 && 0<=y && y<=i-1 ) f[y]++;
    }
    ans=0;
    for (int i=0;i<=n;i++){
        if (ans<f[i]) ans=f[i];
    }
    cout<<ans<<endl;
    return 0;
}
