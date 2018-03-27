#include <stdlib.h>
#include <string.h>
// hard-gawry.cpp
// liniówka dla drzew stopnia <= 4. Generalnie trochę masakra, nie wiem czy się gdzieś nie pomyliłem.
#include<cassert>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define MAX_N 1000001
int t,n,p[MAX_N],deg[MAX_N];
vector<int> s[MAX_N],triples_bunch[MAX_N];
bool odd[MAX_N],forbidden[MAX_N],designated_leaf[MAX_N];
char c[MAX_N+1],k[3]={'K','N','P'};
typedef vector<int> vi;
typedef pair<int,vi> gadget;
void process(const gadget &g,int &balance){
  if(g.second.size()==1){
    c[g.first]='3';
    c[g.second[0]]='2';
    return;
  }
  if(balance>0){
    c[g.first]='3';
    for(int i=0;i<g.second.size();i++)c[g.second[i]]='2';
    balance+=1-g.second.size();
  }else{
    c[g.first]='2';
    for(int i=0;i<g.second.size();i++)c[g.second[i]]='3';
    balance+=g.second.size()-1;
  }
}
main(){
//  scanf("%d",&t);
  t=1;
  assert(t<=20);
  while(t--){
    scanf("%d",&n);
    assert(n%3==0&&n<=500000);
    for(int i=2;i<=n;i++){
      scanf("%d",&p[i]);
      assert(1<=p[i]&&p[i]<i);
      s[p[i]].push_back(i);
      s[i].push_back(p[i]);
    }
    for(int i=1;i<=n;i++)assert(s[i].size()<=4);
    odd[1]=false;
    for(int i=2;i<=n;i++)odd[i]=!odd[p[i]];
    vector<int> a[2];
    for(int i=1;i<=n;i++)a[odd[i]].push_back(i);
    if(a[0].size()>a[1].size())swap(a[0],a[1]);
    //fprintf(stderr,"%d %d\n",a[0].size(),a[1].size());
    if(a[0].size()>=n/3&&a[1].size()>=n/3){
      int take_left=a[0].size()-n/3;
      vector<int> taken;
      for(int i=1;i<=n;i++)forbidden[i]=false;
      for(int i=0;i<a[0].size();i++)c[a[0][i]]='2';
      for(int i=0;i<a[1].size();i++)c[a[1][i]]='3';
      for(int i=0;i<a[0].size();i++)if(s[a[0][i]].size()<=2&&take_left){
        taken.push_back(a[0][i]);
        --take_left;
        c[a[0][i]]='1';
        for(int j=0;j<s[a[0][i]].size();j++)forbidden[s[a[0][i]][j]]=true;
      }
      assert(!take_left);
      vector<int> available;
      for(int i=0;i<a[1].size();i++)if(!forbidden[a[1][i]])available.push_back(a[1][i]);
      assert(available.size()>=n/3-taken.size());
      for(int i=0;i<n/3-taken.size();i++)c[available[i]]='1';
    }else{
      assert(s[0].size()<n/3&&a[1].size()>2*n/3);
      vector<int> leaves;
      for(int i=0;i<a[1].size();i++)if(s[a[1][i]].size()==1)leaves.push_back(a[1][i]);
      while(a[1].size()-leaves.size()<n/3)leaves.pop_back();
      assert(a[1].size()-leaves.size()==n/3);
      for(int i=1;i<=n;i++)c[i]=0;
      for(int i=0;i<a[1].size();i++)c[a[1][i]]='1';
      //fprintf(stderr,"designated leaves on right:");for(int i=0;i<leaves.size();i++)fprintf(stderr," %d",leaves[i]);fprintf(stderr,"\n");
      for(int i=1;i<=n;i++)designated_leaf[i]=false;
      for(int i=0;i<leaves.size();i++)designated_leaf[leaves[i]]=true;
      for(int i=1;i<=n;i++)deg[i]=0;
      // deg[i] is the number of adjacent designated leaves
      for(int i=0;i<leaves.size();i++){
        assert(s[leaves[i]].size()==1);
        ++deg[s[leaves[i]][0]];
      }
      vector<gadget> g;
      vector<int> nonadjacent;
      for(int i=0;i<a[0].size();i++)if(!deg[a[0][i]]){
        nonadjacent.push_back(a[0][i]);
      }else{
        vi nbrs;
        for(int j=0;j<s[a[0][i]].size();j++)if(designated_leaf[s[a[0][i]][j]])nbrs.push_back(s[a[0][i]][j]);
        g.push_back(gadget(a[0][i],nbrs));
      }
      for(int i=0;i<g.size();i++){
        //fprintf(stderr,"%d",g[i].first);
        //for(int j=0;j<g[i].second.size();j++)fprintf(stderr," %d",g[i].second[j]);
        //fprintf(stderr,"\n");
      }
      if(nonadjacent.size()){
        //fprintf(stderr,"nonadjacent\n");  
        int balance=0;
        for(int i=0;i<g.size();i++)process(g[i],balance);
        assert(abs(balance)<=2);
        for(int i=0;i<nonadjacent.size();i++)if(balance>0){
          c[nonadjacent[i]]='2';
          --balance;
        }else{
          c[nonadjacent[i]]='3';
          ++balance;
        }
        assert(!balance);
      }else{
        // everyone on the left is a neighbour of a designated leaf, cool
        for(int i=0;i<g.size();i++)if(g[i].second.size()==2){
          swap(g[i],g.back());
          break;
        }
        int triples=0;
        for(int i=0;i<g.size();i++)triples+=g[i].second.size()==3;
        if(!g.empty()&&g.back().second.size()==2){
          int balance=0;
          for(int i=0;i<g.size();i++)process(g[i],balance);
          assert(!balance);
        }else{
          // now every small gadget is unary or triple, the number of triples is odd, superb!
          int balance=0;
          for(int i=0;i<g.size();i++)if(g[i].second.size()==1)process(g[i],balance);else{
            int other=-1;
            for(int j=0;j<s[g[i].first].size();j++)if(!designated_leaf[s[g[i].first][j]])other=s[g[i].first][j];
            assert(other>-1);
            triples_bunch[other].push_back(i);
          }
          int first_bunch=0;
          while(triples_bunch[first_bunch].empty())++first_bunch;
          for(int i=first_bunch+1;i<=n;i++)for(int j=0;j<triples_bunch[i].size();j++)process(g[triples_bunch[i][j]],balance);
          assert(abs(balance)<=2&&balance%2==0);
          vector<gadget> left;
          for(int i=0;i<triples_bunch[first_bunch].size();i++)left.push_back(g[triples_bunch[first_bunch][i]]);
          if(left.size()==1&&balance||left.size()==2&&!balance||left.size()%3&&balance){
            for(int i=0;i<left.size();i++)process(left[i],balance);
            assert(!balance);
          }else if(left.size()==1){
            c[first_bunch]='2';
            c[left[0].first]='1';
            c[left[0].second[0]]='3';
            c[left[0].second[1]]='2';
            c[left[0].second[2]]='3';
          }else if(left.size()==2){
            assert(balance==2);// the only way to get -2 is to have 0 and subtract 2
            c[first_bunch]='2';
            c[left[0].first]='1';
            c[left[1].second[0]]='3';
            c[left[1].second[1]]='2';
            c[left[1].second[2]]='3';
            c[left[1].first]='3';
            c[left[1].second[0]]='2';
            c[left[1].second[1]]='2';
            c[left[1].second[2]]='2';
          }else if(left.size()==3){
            // we need some help!
            int helper=1;
            while(helper<=n&&(s[helper].size()>1||c[helper]!='1'))++helper;
            assert(helper<=n);
            c[helper]=c[s[helper][0]]=='2'?'3':'2';
            c[first_bunch]='2';
            c[left[0].first]='1';
            c[left[0].second[0]]='2';
            c[left[0].second[1]]='3';
            c[left[0].second[2]]=c[helper]=='2'?'2':'3';
            c[left[1].first]='1';
            c[left[1].second[0]]='3';
            c[left[1].second[1]]='3';
            c[left[1].second[2]]='3';
            c[left[2].first]='3';
            c[left[2].second[0]]='2';
            c[left[2].second[1]]='2';
            c[left[2].second[2]]='2';
          }else assert(0);
        }
      }
    }
    c[n+1]=0;
    for(int i=1;i<=n;i++)c[i]=k[c[i]-'1'];
    printf("%s\n",c+1);
    for(int i=1;i<=n;i++){
      s[i].clear();
      triples_bunch[i].clear();
    }
  }
}

