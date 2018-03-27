#include <cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
using namespace std;
const int maxn=100005;
const int mod=(1<<31)-1;
int mu[maxn+10],notprime[maxn+10],prime[maxn+10],tot;
int F[maxn+10];
void seive()
{
    memset(notprime,0,sizeof(notprime));tot=0;
    mu[1]=1;
    for(int i=2;i<=maxn;i++)
    {
        if(!notprime[i])
        {
            prime[tot++]=i;
            mu[i]=-1;
        }
        for(int j=0;j<tot;j++)
        {
            if(prime[j]*i>maxn) break;
            notprime[prime[j]*i]=1;
            mu[prime[j]*i]=-mu[i];
            if(i%prime[j]==0)
            {
                mu[prime[j]*i]=0;
                break;
            }
        }
    }
}
struct _Pair
{
    int x,y;
    _Pair(){}
    _Pair(int x,int y):x(x),y(y){}
    bool operator<(const _Pair& rhs) const
    {
        return y<rhs.y;
    }
}Pair[maxn+10];
void fx()
{
    for(int i=1;i<=maxn;i++)
        for(int j=i;j<=maxn;j+=i)
            F[j]+=i;
    for(int i=1;i<=maxn;i++)
        Pair[i]=_Pair(i,F[i]);
    sort(Pair+1,Pair+1+maxn);
}
int d[maxn+10];
int lowbit(int x)
{
    return x&(-x);
}
void update(int pos,int v)
{
    while(pos<maxn)
    {
        d[pos]+=v;
        pos+=lowbit(pos);
    }
}
int sum(int pos)
{
    if(pos==0) return 0;
    int res=0;
    while(pos)
    {
        res+=d[pos];
        pos-=lowbit(pos);
    }
    return res;
}
int Q,n,m,a;
struct _query
{
    int n,m,a,id;
    _query(){}
    _query(int n,int m,int a,int id):n(n),m(m),a(a),id(id){}
    bool operator<(const _query& rhs ) const
    {
        return a<rhs.a;
    }
}query[maxn+10];
int ans[maxn+10];
int solve(int n,int m)
{
    if(n>m) swap(n,m);
    int res=0;
    for(int i=1,last=0;i<=n;i=last+1)
    {
        last=min(n/(n/i),m/(m/i));
        res+=(sum(last)-sum(i-1))*(n/i)*(m/i);
    }
    return res;
}
int main()
{
    //freopen("data.in","r",stdin);
    seive();
    fx();
    scanf("%d",&Q);
    for(int i=1;i<=Q;i++)
    {
        scanf("%d%d%d",&n,&m,&a);
        query[i]=_query(n,m,a,i);
    }
    sort(query+1,query+1+Q);
    int head=1;
    for(int i=1;i<=Q;i++)
    {
        while(head<maxn&&Pair[head].y<=query[i].a)
        {
            for(int i=Pair[head].x;i<=maxn;i+=Pair[head].x)
            {
                update(i,Pair[head].y*mu[i/Pair[head].x]);
            }
            head++;
        }
        ans[query[i].id]=solve(query[i].n,query[i].m)&mod;
    }
    for(int i=1;i<=Q;i++)
        printf("%d\n",ans[i]);
    return 0;
}
