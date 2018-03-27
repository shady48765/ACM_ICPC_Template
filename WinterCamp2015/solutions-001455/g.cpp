#include <stdlib.h>
#include <string.h>
// hard-gawry.cpp
#include<cstdio>
// O(nklogn)
#include<cstdio>
#include<cassert>
#include<vector>
#include<algorithm>
#include<set>
using namespace std;
#define INF 700000000
#define MAX_N 20000
#define MAX_K 100
int t,n,k,a[MAX_N],best[MAX_K+1][MAX_N],where[MAX_N],sa[MAX_N],where2[MAX_N];
bool cmp_a(int x,int y){
  return a[x]<a[y]||a[x]==a[y]&&x<y;
}
#define POWER (1<<16)
int power,s[2*POWER];
pair<long long,int> tmp[MAX_N];
int get(int bound){
  int ans=-1;
  bound+=power;
  while(bound>1){
    if(bound%2&&(ans==-1||a[s[bound-1]]>a[ans]))ans=s[bound-1];
    bound/=2;
  }
  return ans;
}
void update(int pos,int val){
  pos+=power;
  while(pos){
    if(s[pos]==-1||(a[val]>a[s[pos]]))s[pos]=val;
    pos/=2;
  }
}
main(){
    scanf("%d %d",&n,&k);
    assert(1<=n&&n<=MAX_N);
    assert(1<=k&&k<=MAX_K);
    for(int i=0;i<n;i++){
      scanf("%d",&a[i]);
      assert(1<=a[i]&&a[i]<=INF);
    }
    if(k==1){
      printf("1\n");
      return 0;
    }
    typedef pair<int,int> p2;
    set<p2> seen;
    for(int i=0;i<n;i++){
      set<p2>::iterator it=seen.lower_bound(p2(a[i],-1));
      best[2][i]=-1;
      if(it!=seen.begin()){
        --it;
        best[2][i]=it->second;
      }
      seen.insert(p2(a[i],i));
    }
    for(int i=0;i<n;i++)sa[i]=i;
    sort(sa,sa+n,cmp_a);
    for(int len=3;len<=k;len++){
      for(int j=0;j<n;j++)if(best[len-1][j]>-1)tmp[j]=make_pair(2LL*a[j]-a[best[len-1][j]],j);
      sort(tmp,tmp+n);
      int k=0,size=0;
      for(int j=0;j<n;j++){
        size+=j&&tmp[j-1].first<tmp[j].first;
        while(k<n&&a[sa[k]]<=tmp[j].first)where2[sa[k++]]=size;
        where[tmp[j].second]=size;
      }
      ++size;
      while(k<n)where2[sa[k++]]=size;
      power=1;
      while(power<size)power*=2;
      for(int j=1;j<2*power;j++)s[j]=-1;
      for(int i=0;i<n;i++){
        best[len][i]=get(where2[i]);
        if(best[len-1][i]>-1)update(where[i],i);
      }
    }
    int pos=0;
    while(pos<n&&best[k][pos]==-1)++pos;
    if(pos==n){
      printf("NO\n");
      return 0;
    }
    vector<int> ans;
    for(int len=k;len;len--){
      assert(pos>-1);
      ans.push_back(pos);
      pos=best[len][pos];
    }
    reverse(ans.begin(),ans.end());
    for(int i=0;i<k;i++)printf("%d%c",1+ans[i],i+1<k?' ':'\n');
}

