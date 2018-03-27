#include <iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
struct Node{
    int x,y;
}ans[100];
int l,s,a,b,x,y;
long long smax,smin;
int main()
{
    cin>>l>>s;
    if (l%2==1) {
        cout<<"-1"<<endl;
    }
    l/=2;
    smax=(l/2)*((l+1)/2);
    smin=l-1;
    if (!(smin<=s && s<=smax)) {
        cout<<"-1"<<endl;
    }
    a=(l/2);
    b=(l+1)/2;
    x=(s-smin)/(a-1);
    y=(s-smin)%(a-1);

    ans[1].x=0;ans[1].y=0;
    ans[2].x=0;ans[2].y=b;
    ans[3].x=1;ans[3].y=b;
    ans[4].x=1;ans[4].y=x+1;
    ans[5].x=1+y,ans[5].y=x+1;
    ans[6].x=1+y;ans[6].y=x;
    ans[6].x=a;ans[6].y=x;
    ans[7].x=0;ans[7].y=0;

    cout<<7<<endl;
    for (int i=1;i<=7;i++){
        cout<<ans[i].x<<" "<<ans[i].y<<endl;
    }
    return 0;
}
