#include <cstdio>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;
typedef long long LL;
struct hp
{
    int id;
    int now,tot;
    hp(){}
    hp(int id,int now,int tot):id(id),now(now),tot(tot){}
};
hp HP[32770];
hp ini[32770];
vector<int> ans;
int main()
{
    int T,n,k,a;
    scanf("%d",&T);
    while(T--)
    {
        ans.clear();
        scanf("%d%d",&n,&k);
        for(int i=0;i<(1<<n);i++)
        {
            scanf("%d",&a);
            HP[i]=hp(i,a,a);
            ini[i]=HP[i];
        }
        for(int j=n;j>=1;j--){
        for(int i=0;i<(1<<j);i+=2)
        {
            if(HP[i].now>=HP[i+1].now)
                HP[i/2]=hp(HP[i].id,HP[i].now-HP[i+1].now,HP[i].tot);
            else HP[i/2]=hp(HP[i+1].id,HP[i+1].now-HP[i].now,HP[i+1].tot);
            HP[i/2].now=min(HP[i/2].tot,HP[i/2].now+k);
        }
        }
        printf("%d\n",HP[0].id+1);
        int win=HP[0].id;
        for(int j=n;j>=1;j--){
        for(int i=0;i<(1<<j);i+=2)
        {
            if(ini[i].id==win||ini[i+1].id==win)
            {
            if(ini[i].now>=ini[i+1].now)
            {
                ans.push_back(ini[i+1].id);
                ini[i/2]=hp(ini[i].id,ini[i].now-ini[i+1].now,ini[i].tot);
            }
            else
            {
                ans.push_back(ini[i].id);
                ini[i/2]=hp(ini[i+1].id,ini[i+1].now-ini[i].now,ini[i+1].tot);}
                ini[i/2].now=min(ini[i/2].tot,ini[i/2].now+k);
            }
            else
            {
            if(ini[i].now>=ini[i+1].now)
                ini[i/2]=hp(ini[i].id,ini[i].now-ini[i+1].now,ini[i].tot);
            else ini[i/2]=hp(ini[i+1].id,ini[i+1].now-ini[i].now,ini[i+1].tot);
            ini[i/2].now=min(ini[i/2].tot,ini[i/2].now+k);
            }
        }
        }
        bool fst=true;
        for(int i=0;i<ans.size();i++)
        if(fst) {printf("%d",ans[i]+1);fst=false;}else
            printf(" %d",ans[i]+1);
        printf("\n");
    }
    return 0;
}
