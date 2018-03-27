#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
int myabs(int x)
{
    if(x<0) return -x;
    else return x;
}
struct node
{
    int k,a,b;
    node(){}
    node(int k,int a,int b):k(k),a(a),b(b){}
};
bool cmp(node A,node B)
{
    return myabs(A.a-A.b)>myabs(B.a-B.b);
}
vector<node> G;
int main()
{
    int n,A,B,k,da,db;
    while(scanf("%d%d%d",&n,&A,&B)&&(n+A+B))
    {
        G.clear();
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d",&k,&da,&db);
            G.push_back(node(k,da,db));
        }
        sort(G.begin(),G.end(),cmp);
       int res=0;
        for(int i=0;i<G.size();i++)
        {
            if(G[i].a>=G[i].b)
            {
                if(B>=G[i].k){
                    res+=G[i].k*G[i].b;
                    B-=G[i].k;
                }
                else
                {
                    res+=B*G[i].b;
                    G[i].k-=B;
                    B=0;
                    res+=G[i].k*G[i].a;
                    A-=G[i].k;
                }
            }
            else if(G[i].a<G[i].b)
            {
                if(A>=G[i].k)
                {
                    res+=G[i].k*G[i].a;
                    A-=G[i].k;
                }
                else
                {
                    res+=A*G[i].a;
                    G[i].k-=A;
                    A=0;
                    res+=G[i].k*G[i].b;
                    B-=G[i].k;
                }
            }

        }
        printf("%d\n",res);
    }
    return 0;
}
