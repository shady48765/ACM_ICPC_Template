#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include<cstdio>
#include<vector>
using namespace std;
const int MAX=1100000;
int n,p[MAX];
vector<int> s[MAX];
// traverses the tree rooted at root, starting at root and ending at its children, unless the tree consists just of one node
void solve(int root,bool reverse=false){
  vector<int> res;
  if(!reverse){
    printf("%d\n",root);
  }
  for(int i=0;i<s[root].size();i++){
    solve(s[root][i],!reverse);
  }
  if(reverse){
    printf("%d\n",root);
  }
}
int main(){
  scanf("%d",&n);
  for(int i=2;i<=n;i++){
    scanf("%d",&p[i]);
    s[p[i]].push_back(i);
  }
  solve(1);
  return 0;
}
