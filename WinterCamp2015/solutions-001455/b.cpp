#include <stdlib.h>
#include <string.h>
#include <algorithm>
// hard-gawry.cpp
#include<cstdio>
#include<cstdio>
#include<cassert>
#include<vector>
using namespace std;
const int MAX=60;
int k,next[MAX];
main(){
    scanf("%d",&k);
    assert(k==2||k%2);
    if(k==2){
      puts("1 2 1 1");
      puts("1 2 2 2");
      puts("2 2 2 1");
      puts("1 1 2 1");
      return 0;
    }
    for(int i=0;i<k;i++)next[i]=0;
    vector<int> q,r;
    q.push_back(0);
    while(!q.empty()){
      int top=q.back();
      if(next[top]<k){
        q.push_back(next[top]);
        ++next[top];
      }else{
        q.pop_back();
        r.push_back(top+1);
      }
    }
    r.pop_back();
    assert(r.size()==k*k);
    int diff=0;
    for(int j=0;j<k*k;j++){
      for(int i=0;i<r.size();i++)printf("%d%c",r[(i+diff)%r.size()],i+1<r.size()?' ':'\n');
      diff=(diff+j)%(k*k);
    }
}

