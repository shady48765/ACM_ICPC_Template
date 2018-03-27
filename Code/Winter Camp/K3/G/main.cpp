#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
int cnt,n,m,x,y;
int vis[1001000];
int main()
{
    cin>>n>>m;
    cnt=0;
    memset(vis,0,sizeof(vis));
    for (int i=1;i<=m;i++){
        scanf("%d%d",&x,&y);
        if (x>y) {
            cout<<"No"<<endl;
            return 0;
        }
        if (y==x+1) {
                vis[x]=1;
  //      cout<<x<<endl;
        }
    }
    for (int i=1;i<=n-1;i++){
        cnt+=vis[i];
    }
//    cout<<"n="<<n<<endl;
    if (cnt==n-1){
        cout<<"Yes"<<endl;
    }else {
        cout<<"No"<<endl;
    }
    return 0;
}
