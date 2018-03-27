#include <cstdio>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
struct node
{
    int id;
    long long now;
    node(){}
    node(int id,long long now):id(id),now(now){}
    void add(int x)
    {
        now+=(long long)x;
    }
    bool operator<(const node& rhs)const
    {
        return now>rhs.now||(now==rhs.now&&id>rhs.id);
    }
}t1,t2,last;
int A[200010];
int n,m,x,y;
long long  tmp,ans;
priority_queue<node> q;
int main()
{
    scanf("%d%d%d%d",&n,&m,&x,&y);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&A[i]);
        q.push(node(i,(long long )A[i]));
    }
    ans=A[1]+y;
    if (n==1) {
            ans=(long long )A[1]+y+m*x;
            cout<<ans<<endl;
            return 0;
    }
    int cnt=0;
    while (m--){
        t1=q.top();
        q.pop();
      //  cout<<t1.id<<" "<<t1.now<<endl;
        if (t1.id==1) {
            if (y>=x){
                m++;
                y-=x;
            }
            tmp=t1.now+x;
        }
        t1.add(x);
        last=t1;
        q.push(t1);
    }
   // cout<<tmp<<" "<<last.id<<" "<<last.now<<endl;
  //  cout<<y<<endl;
    if (last.id==1){
        while (last.id==1) {
                last=q.top();
                q.pop();
        }
     //   cout<<last.id<<" "<<last.now<<endl;
        ans=max(ans,tmp-x+max((long long)0,min((long long)(y),last.now-tmp+x))+x);
        // ans=max(ans,tmp-x+max((long long)0,min((long long)(y+x),last.now-tmp))+x);
    }
    else
        ans=max(ans,tmp-x+max((long long)0,min((long long)(y+x),last.now-tmp))+x);
  //  cout<<min((long long)(y+x),last.now-tmp+x)<<endl;
        //ans=max(ans,tmp-x+max((long long)0,min((long long)(y),last.now-tmp))+x);
 //   else
  //      ans=max(ans,tmp-x+max((long long)0,min((long long)(y),last.now-tmp)));
    printf("%lld\n",ans);
    return 0;
}

