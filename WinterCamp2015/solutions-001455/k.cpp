#include <stdlib.h>
#include <string.h>
#include <algorithm>
// nobel-hard.cpp
#include<cstdio>
#include<iostream>
#include<cassert>
using namespace std;
int f(int n,int k){return (n+n-k+1)*k/2;}
int c,n,s,k;
main(){
  scanf("%d",&c);
  assert(c<=8000);
  while(c--){
    scanf("%d %d %d",&n,&s,&k);
    assert(n<=40000);
    assert(1<=k&&k<=n);
    assert(0<=s&&s<=1000000000);
    bool taken[n+1];
    for(int i=1;i<=n;i++)taken[i]=false;
    int min=k*(k+1)/2,nn=n;
    if(k>n||s<min||s>f(n,k)){
      puts("NO");
      continue;
    }
    puts("YES");
    while(k){
      while(f(nn-1,k)>=s)nn--;
      taken[nn]=true;
      s-=nn;
      k--;
      nn--;
    }
    for(int i=1;i<=n;i++)printf("%d",(int)taken[i]);
    puts("");
  }
}
