#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*---------------*/
/* Parenthesis 4 */
/*   Darsein AC  */
/*---------------*/

#include<iostream>
#include<vector>
#include<queue>
#include<map>
#include<algorithm>
#include<cassert>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef vector<int> vi;

int n;
string s;
vector< vi > g;
vector< deque<ll> > lq,rq;
vector<int> p;

pll calc(int v, int par){
  ll ans = 0, nums = 1, L = v;
  vector<pll> child;

  //recursive calculation for subtree
  for(int u : g[v]){
    if(u != par){
      pll tmp = calc(u,v);
      child.push_back( pll(tmp.second, p[u]) );
      ans += tmp.first; nums += tmp.second;
    }
  }

  sort(child.begin(), child.end(), greater<pll>());

  if(child.empty()){
    L = p[v] = v;
    lq[L].push_back(0); rq[L].push_back(0);
  }else L = p[v] = child[0].second;

  //preprocess largest subtree
  if(s[v] == '('){
    lq[L].push_front(0); lq[L][1]++;
    rq[L].pop_front();
    if(rq[L].empty())rq[L].push_front(0);
    ans += rq[L][0];
  }else{
    rq[L].push_front(0); rq[L][1]++;
    lq[L].pop_front();
    if(lq[L].empty())lq[L].push_front(0);
    ans += lq[L][0];
  }
  
  for(pll tmp : child){
    int u = tmp.second;
    if(u == L)continue;
    
    if(s[v] == '('){
      while(lq[L].size()<lq[u].size()+1)lq[L].push_back(0);
      while(rq[L].size()<rq[u].size())rq[L].push_back(0);
    }else{
      while(lq[L].size()<lq[u].size())lq[L].push_back(0);
      while(rq[L].size()<rq[u].size()+1)rq[L].push_back(0);
    }

    //calculate answer
    for(int i=0;i<(int)min(lq[L].size(), rq[u].size());i++){
      ans += lq[L][i] * rq[u][i];
    }
    for(int i=0;i<(int)min(lq[u].size(), rq[L].size());i++){
      ans += rq[L][i] * lq[u][i];
    }
    
    //merge
    if(s[v] == '('){
      for(int i=0;i<(int)lq[u].size();i++)lq[L][i+1] += lq[u][i];      
      for(int i=1;i<(int)rq[u].size();i++)rq[L][i-1] += rq[u][i];
    }else{
      for(int i=1;i<(int)lq[u].size();i++)lq[L][i-1] += lq[u][i];      
      for(int i=0;i<(int)rq[u].size();i++)rq[L][i+1] += rq[u][i];
    }
  }

  return pll(ans, nums);
}

int main(){
  cin.tie(0); ios::sync_with_stdio(0);

  cin >> n >> s;
  g.resize(n);
  for(int i=0;i<n-1;i++){
    int a,b;
    cin >> a >> b; a--; b--;
    g[a].push_back(b); g[b].push_back(a);
  }

  lq.resize(n); rq.resize(n);
  p.resize(n);
  cout << calc(0,-1).first  << endl;
  return 0;
}
