#include <iostream>
#include<algorithm>
#include <vector>
#include <cstdio>
#define rep(i,l,r) for (long long i=l;i<=r;i++)
using namespace std;
struct Node{
    int l,r;
    unsigned long long f;
}tmpNode;
vector<Node> q;
int n,m;
int a[3000],l[3000],r[3000];
int tmp;
long long ans;
unsigned long long P[200000],f[1200][1200];
unsigned long long Get(int i,int j){
    if (i==j) return 1e9+7;
    long long re;
    re=P[i-j];
 //   cout<<"re="<<re<<endl;
    re*=r[j-1]+1;
  //  cout<<"re="<<re<<endl;
    re+=f[i][j-1];
    return re;
}
bool cmp(Node a,Node b){
    if (a.f==b.f && a.l==b.l) return a.r>b.r;
    if (a.f==b.f) return  a.l<b.l;
    return a.f<b.f;
}
int main()
{
    scanf("%d%d",&n,&m);
    for (int i=1;i<=m;i++){
        scanf("%d",&a[i]);
    }
    rep (i,0,m) P[1]=1000000007;
    if (m==0) {
        cout<<n<<endl;
        return 0;
    }
    a[m+1]=n+1;
    rep(i,1,m) l[i]=a[i]-1-a[i-1],ans=max(ans,(long long) l[i]);
    rep(i,1,m) r[i]=a[i+1]-1-a[i],ans=max(ans,(long long) r[i]);
    r[0]=l[1];l[m+1]=r[m];
    rep(i,1,m) cout<<i<<" "<<l[i]<<" "<<r[i]<<endl;
 //   rep(i,1,m) cout<<l[i]<<" "<<r[i]<<endl;
  //  rep(i,1,m) b[++num]=a[i]-a[i-1]-1,b[++num]=-100007;b[++num]=r[n];
    rep(i,1,m) rep(j,i,m) {
        f[i][j]=Get(i,j);
        tmpNode.l=l[i];
        tmpNode.r=r[j];
        tmpNode.f=f[i][j];
        q.push_back(tmpNode);
       cout<<i<<" "<<j<<" "<<f[i][j]<<endl;
    }
//    cout<<q.size()<<endl;
    sort(q.begin(),q.end(),cmp);
    tmp=0;
  //  cout<<"ans="<<ans<<endl;
  //  cout<<"tmp="<<tmp<<endl;
    //rep(i,q.begin,q.end()-1){
  //  cout<<"!"<<endl;
    for (int i=0;i<q.size();i++){
        cout<<q[i].l<<" "<<q[i].r<<" "<<q[i].f<<endl;
        if (i==0) tmp=0,ans+=(long long )(q[i].l+1)*(q[tmp].r+1);
        else if (q[i].f!=q[i-1].f) tmp=i,ans+=(long long )(q[i].l+1)*(q[tmp].r+1);
        else if (q[i].l!=q[i-1].l) tmp=i,ans+=(long long )(q[i].l-q[i-1].l)*(q[tmp].r+1);
        cout<<ans<<endl;
    }
    cout<<ans<<endl;
    return 0;
}
