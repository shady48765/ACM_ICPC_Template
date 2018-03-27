#include <iostream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<vector>
#include<cstring>
using namespace std;
int n,m;
string name[4040];
struct p
{
    int id,dis;
    p(){}
    p(int id,int dis):id(id),dis(dis){}
    bool operator<(const p& rhs) const
    {
        return dis<rhs.dis;
    }
};
vector<p> boy;
vector<p> girl;
int d;
int dist[4040];
vector<int> C;
int main()
{
    freopen("taxi.in","r",stdin);
    boy.clear();girl.clear();C.clear();
    cin>>n;
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        ++cnt;
        cin>>name[cnt]>>d;
        dist[cnt]=d;
        boy.push_back(p(cnt,d));
    }
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        ++cnt;
        cin>>name[cnt]>>d;
        dist[cnt]=d;
        girl.push_back(p(cnt,d));
    }
    sort(boy.begin(),boy.end());
    sort(girl.begin(),girl.end());
    int q1=n-1;
    int q2=m-1;

    while(n+m>=4)
    {
        for(int i=4;i>=1;i--)
        {
            if(i>n||4-i>m) continue;
            if(boy[q1-i+1].dis<=girl[q2-(4-i)+1].dis&&i!=1) continue;
            if(3*(n-i)<m-4+i) continue;
            for(int k=0;k<i;k++)
                C.push_back(boy[q1-k].id);
            for(int k=0;k<4-i;k++)
                C.push_back(girl[q2-k].id);
            C.push_back(-1);
            n-=i;
            q1-=i;
            m-=(4-i);
            q2-=(4-i);
            break;
        }
    }
    for(int i=0;i<=q1;i++)C.push_back(boy[i].id);
    for(int i=0;i<=q2;i++)C.push_back(girl[i].id);
    C.push_back(-1);
    int maxx=-999,res=0,ccnt=0;
    for(int i=0;i<C.size();i++)
    {
        if(C[i]==-1) ccnt++,res+=maxx,maxx=-999;
        else
        {
            maxx=max(dist[C[i]],maxx);
        }
    }
    printf("%d\n%d\n",res,ccnt);
    int now=0,lst=0;
    for(int i=1;i<=ccnt;i++)
    {
        while(lst<C.size()&&C[lst]!=-1) lst++;
        printf("Taxi %d: ",i);
        for(int kk=1;kk<=lst-now;kk++)
        {
            if(lst-now==1)
                printf("%s.\n",name[C[now+kk-1]].c_str());
            else if(kk==1)
                printf("%s",name[C[now+kk-1]].c_str());
            else if(kk!=lst-now)
                printf(", %s",name[C[now+kk-1]].c_str());
            else printf(" and %s.\n",name[C[now+kk-1]].c_str());
        }
        now=lst+1;
        lst+=1;
    }
    return 0;
}
