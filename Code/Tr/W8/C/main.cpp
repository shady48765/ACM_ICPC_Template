#include <iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=1000010;
struct _node
{
    int a,id;
}node[maxn];
int n,k1,k2;
bool cmp(_node a,_node b)
{
    return a.a<b.a;
}
bool cmp2(_node a,_node b)
{
    return a.id<b.id;
}
vector<_node> G1,G2;
int main()
{
    int kase=0;
    while(scanf("%d%d%d",&n,&k1,&k2)&&(n+k1+k2))
    {
        ++kase;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&node[i].a);
            node[i].id=i;
        }
        stable_sort(node+1,node+1+n,cmp);
        G1.clear();G2.clear();
        for(int i=1;i<=k1;i++) G1.push_back(node[i]);
        for(int i=n,j=1;j<=k2;j++,i--) G2.push_back(node[i]);
        sort(G1.begin(),G1.end(),cmp2);
        sort(G2.begin(),G2.end(),cmp2);
        printf("Case %d\n",kase);
        bool fst=true;
        for(int i=0;i<k1;i++)
            if(fst)
            printf("%d",G1[i].id),fst=false;
            else printf(" %d",G1[i].id);
        printf("\n");
        fst=true;
        for(int i=k2-1;i>=0;i--)
            if(fst)
            printf("%d",G2[i].id),fst=false;
            else printf(" %d",G2[i].id);
        printf("\n");

    }
    return 0;
}
