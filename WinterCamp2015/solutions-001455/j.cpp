#include <stdlib.h>
#include <string.h>
// cenzura.cpp
#include<cstdio>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
#define MAX 201000
#define INF 2000000000
int c[26],pi[MAX],rightmost[MAX],inside[MAX],start[MAX],end[MAX];
char text[MAX],forbidden[MAX];
typedef pair<int,int> p2;
vector<p2> interval[MAX];
int main() {
  int n=0,k,m,i,j,z;
  gets(text); while (text[n]) n++;
  for (i=0; i<n; i++) rightmost[i]=MAX;
  scanf("%d\n",&k);
  // budujemy wiezy
  for (z=0; z<k; z++) {
    gets(forbidden); m=0; while (forbidden[m]) m++;
    for (i=2,j=0; i<=m; i++) {
      while (j && forbidden[j]!=forbidden[i-1]) j=pi[j];      
      pi[i]=j+=forbidden[j]==forbidden[i-1];
    }
    j=0;
    for (i=0; i<n; i++) {
      while (j && forbidden[j]!=text[i]) j=pi[j];
      j+=forbidden[j]==text[i];
      if (j==m) {
        j=pi[j];
        rightmost[i]=min(rightmost[i],m);
      }
    }
  }
  for (i=0; i<26; i++) scanf("%d",&c[i]);
  // usuwamy zagniezdzenia
  vector<p2> q;
  for (i=n-1; i>=0; i--) if (rightmost[i]<MAX) {
    while (!q.empty() && i-rightmost[i]+1>=q.back().first) q.pop_back();
    q.push_back(p2(i-rightmost[i]+1,i));
  }
  reverse(q.begin(),q.end());
  // wyznaczamy zakresy
  for (i=0; i<n; i++) {
    start[i]=-1;
    end[i]=MAX;
  }
  for (i=0; i<q.size(); i++) {
    inside[q[i].first]++;
    inside[q[i].second+1]--;
    start[q[i].first]=end[q[i].second]=i;
  }
  for (i=0; i<n; i++) {
    inside[i+1]+=inside[i];
    start[i+1]=max(start[i+1],start[i]);
  }
  for (i=n-1; i; i--) end[i-1]=min(end[i-1],end[i]);
  for (i=0; i<n; i++) if (inside[i]) interval[start[i]+1].push_back(p2(end[i],c[text[i]-'a']));
  // i jedziemy ;)
  vector<p2> stack(1,p2(0,0));
  for (i=1; i<=q.size(); i++) {
    z=INF;
    for (j=0; j<interval[i].size(); j++)
      z=min(z,lower_bound(stack.begin(),stack.end(),p2(interval[i][j].first,0))->second+interval[i][j].second);
    while (stack.size() && stack.back().second>=z) stack.pop_back();
    stack.push_back(p2(i,z));
  }
  printf("%d\n",stack.back().second);

  return 0;
}
