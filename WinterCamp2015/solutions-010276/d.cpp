#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

int W;
int cycle[500010];
int elcyc[500010];

int func(int x, int h1, int h2){
	if(h1 < h2 && h1 % 2 == 1 && x != 0 && x != W-1){
		x = ((x - 1) ^ 1) + 1;
		h1++;
	}
	
	int steps = (h2 - h1) / 2;
	x = cycle[(elcyc[x] + steps) % W];
	h1 += 2 * steps;
	
	if(h1 < h2) x ^= 1;
	
	return x;
}

vector <pair <int, int> > v;
int p[500010];

int main(void){
	int H,N,i;
	
	cin >> H >> W >> N;
	REP(i,N){
		int a,b;
		scanf("%d%d", &a, &b);
		v.push_back(make_pair(a-1, b-1));
	}
	sort(v.begin(),v.end());
	
	REP(i,W/2) cycle[i] = 2*i;
	REP(i,W/2) cycle[W/2+i] = W-1-2*i;
	REP(i,W) elcyc[cycle[i]] = i;
	
	REP(i,W) p[i] = i;
	
	for(i=N-1;i>=0;i--){
		int a = v[i].first, b = v[i].second;
		int x = func(b, a, H);
		int y = func(b+1, a, H);
		swap(p[x], p[y]);
	}
	
	REP(i,W){
		int x = func(i, 0, H);
		printf("%d\n", p[x]+1);
	}
	
	return 0;
}
