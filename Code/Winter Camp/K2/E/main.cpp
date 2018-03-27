#include <iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct Node{
    int x,y;
}ans[100],aa[100];
int l,s,a,b,x,y,now;
long long smax,smin;
int main()
{
    cin>>l>>s;
    if (l%2==1) {
        cout<<"-1"<<endl;
        return 0;
    }
    l/=2;

    smax=(long long )(l/2)*((l+1)/2);
    smin=l-1;
 //   cout<<"smax=="<<smax<<endl;
 //   cout<<"smin=="<<smin<<endl;
    if (!(smin<=s && s<=smax)) {
        cout<<"-1"<<endl;
        return 0;
    }
    a=(l/2);
    b=(l+1)/2;
  //  cout<<a<<" "<<b<<endl;
    if (a==1) {
            cout<<4<<endl;
        ans[1].x=0;ans[1].y=0;
        ans[2].x=0;ans[2].y=b;
        ans[3].x=1;ans[3].y=b;
        ans[4].x=1;ans[4].y=0;
        for (int i=1;i<=4;i++)
            cout<<ans[i].x<<" "<<ans[i].y<<endl;
        return 0;
    }

    x=(s-smin)/(a-1);
    y=(s-smin)%(a-1);
//    cout<<(s-smin)<<" "<<x<<" "<<y<<endl;
//    cout<<y+x*(a-1)<<endl;
//    cout<<x<<" "<<y<<endl;
//    now==1;
    ans[1].x=0;ans[1].y=0;
    ans[2].x=0;ans[2].y=b;
    ans[3].x=1;ans[3].y=b;
    ans[4].x=1;ans[4].y=x+1+1;
    if (y==0) ans[4].y--;
    ans[5].x=1+y,ans[5].y=x+1+1;
    if (y==0) ans[5].y--;
    ans[6].x=1+y;ans[6].y=x+1;
    ans[7].x=a;ans[7].y=x+1;
    ans[8].x=a;ans[8].y=0;

    now=1;
    aa[1]=ans[1];
    for (int i=2;i<=8;i++){
        if (!(ans[i].x==ans[i-1].x && ans[i].y==ans[i-1].y)) aa[++now]=ans[i];
    }
    cout<<now<<endl;
    for (int i=1;i<=now;i++){
        cout<<aa[i].x<<" "<<aa[i].y<<endl;
    }
    return 0;
}
