#include <iostream>
#include<cstdio>
#include<vector>
#include<map>
#include<cstring>
using namespace std;
const int maxn=1000000;
int prime[1000],tot=0;
vector<int> G[maxn+10];
int min_prime[maxn+10];
int A[maxn+10];
void get()
{
    for(int i=1;i<=maxn;i++) min_prime[i]=i;
    for(int i=2;i<=maxn;i++)
    {
        if(min_prime[i]==i) prime[tot++]=i;
        for(int j=0;j<tot;j++)
        {
            if(i*prime[j]>maxn) break;
            min_prime[i*prime[j]]=prime[j];
          //  if(i*prime[j]==4) printf("### %d\n",prime[j]);
            if(i%prime[j]==0) break;
        }
    }
}
void get2()
{
    for(int i=2;i<=maxn;i++)
    {
        int now=i;
        while(min_prime[now]!=1)
        {
            printf("%d\n",now);
            printf("%d\n",G[i].size());
            G[i].push_back(min_prime[now]);
           // printf("hee\n");
            //if(i==4) printf("%d %d\n",i,min_prime[4]);
            int tp=min_prime[now];
            while(now%tp==0)
                now/=tp;
        }
    }
}
bool has[maxn];
long long cnt=0;
void dfs(int pos,int i,int now)
{
    if(now*A[pos]>maxn) return ;
    now*=G[A[pos]][i];

    int f=A[pos]/now;
    int ff=A[pos]*now;
        printf("pos=%d %d %d %d %d\n",pos,now,A[pos],f,ff);
    if(has[f]&&has[ff]){
        ++cnt;
    }
    if(A[pos]%(now*G[A[pos]][i])==0)
        dfs(pos,i,now);
    if(i+1<G[A[pos]].size())
        dfs(pos,i+1,now);

}
int main()
{
    //G[1].push_back(2);
    get();
    get2();
    printf("hehe\n");
    printf("%d\n",G[4][0]);
    memset(has,false,sizeof(has));
    int n,x;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {scanf("%d",&x);has[x]=1;A[i]=x;}
    for(int i=2;i<=n-1;i++)
    {
        dfs(i,0,1);
    }
    printf("%lld",cnt);
    return 0;
}
