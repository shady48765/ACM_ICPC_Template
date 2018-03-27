#include <cstdio>
#include<algorithm>
#include<queue>
#include<cstring>
#include<vector>
using namespace std;
struct item
{
    int s,n;
    item(){}
    item(int s,int n):s(s),n(n){}
    bool operator<(const item& rhs) const
    {
        return n<rhs.n;
    }
};
priority_queue<item> q;
vector<int> ans;
int main()
{
    int n,m,a;
    item tp(0,0),t(0,0);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
    {
        scanf("%d",&a);
        q.push(item(i,a));
    }
    a=n;
    while(!q.empty()&&n>0)
    {
        t=q.top();q.pop();
        if(tp.n>0) q.push(tp);
        tp=item(t.s,t.n-1);
        ans.push_back(tp.s),--n;
    }
    bool ok=true;
    if(ans[a-1]==ans[0])
    {
        ok=false;
        while(!q.empty())
        {
            t=q.top();q.pop();
            if(t.s!=ans[a-2]) {ans[a-1]=t.s;ok=true;break;}
        }
        if(!ok)
        if(ans[a-3]!=ans[a-1])
        {
            swap(ans[a-2],ans[a-1]);
            ok=true;
        }
    }
    if(n>0||!ok) printf("-1");
    else for(int i=0;i<ans.size();i++)
        printf("%d ",ans[i]);
    return 0;
}
