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
        return now>rhs.now||now==rhs.now&&id>rhs.id;
    }
}t1,t2;
int A[200010];
int n,m,x,y;
long long  res;
priority_queue<node> q;
int main()
{
    scanf("%d%d%d%d",&n,&m,&x,&y);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&A[i]);
        q.push(node(i,(long long )A[i]));
    }

    int cnt=0;
    long long last=-1;
    long long alast=A[1];
    long long anow=A[1];
    while(m--)
    {
        t1=q.top();q.pop();
        if(t1.id==1)
        {
            if(y>=x)
            {
                ++cnt;
                m++;
                y-=x;
                alast=t1.now;
                anow=t1.now+x;
            }
            else
            {
                ++cnt;
                alast=t1.now;
                anow=t1.now+x;
            }

        }
        t1.add(x);
        q.push(t1);
    }
    if(cnt==0||n==1)
        res=anow+y;
    else
    {
        t1=q.top();q.pop();
        if(t1.id==1)
            t1=q.top();
        last=t1.now;
    }
       // cout<<last<<" "<<alast<<endl;
        res=anow+min((long long)(x+y),last-anow);

    printf("%lld\n",res);
    return 0;
}

