#include <string.h>
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define UNS64 "%I64u"
#else
#define UNS64 "%llu"
#endif
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

typedef long long ll;

int ID;

int N;
vector <int> child[200010];
int parent[200010];
int gparent[20][200010];
int d[200010];
ll depth[200010];
int depth1[200010];
int L[200010],R[200010];
int order[200010];
set <int> ids;

#define T (1<<18)
int bit[T];

void add(int pos, int val){
	for(int i=pos;i<T;i=((i)|(i+1))) bit[i] += val;
}

int sum(int pos){
	int ans = 0;
	for(int i=pos;i>0;i=((i)&(i-1))) ans += bit[i-1];
	return ans;
}

void dfs(int x, ll dsum, int dsum1){
	depth[x] = dsum;
	depth1[x] = dsum1;
	L[x] = ID;
	order[ID] = x;
	ID++;

	int i;
	REP(i,child[x].size()){
		int y = child[x][i];
		dfs(y, dsum + d[y], dsum1 + 1);
	}

	R[x] = ID;
}

void prelca(void){
	int i,j;
	REP(i,N) gparent[0][i] = parent[i];
	REP(i,19) REP(j,N) gparent[i+1][j] = gparent[i][gparent[i][j]];
}

int lca(int x, int y){
	int i;

	if(depth1[x] > depth1[y]) swap(x, y);
	for(i=17;i>=0;i--) if(depth1[y] - (1<<i) >= depth1[x]) y = gparent[i][y];
	for(i=17;i>=0;i--) if(gparent[i][x] != gparent[i][y]){
		x = gparent[i][x];
		y = gparent[i][y];
	}

	if(x == y) return x;
	return parent[x];
}

void add_vertex(int x){
	ids.insert(L[x]);
	add(L[x], 1);
}

ll dist(int x, int y){
	int p = lca(x, y);
	return depth[x] + depth[y] - 2 * depth[p];
}

int center(int x, int y, int z){
	int p = lca(x, y), q = lca(y, z), r = lca(z, x);
	if(p == q) return r;
	if(q == r) return p;
	return q;
}

int count_child(int x){
	return sum(R[x]) - sum(L[x]);
}

int func(int x, int y, int cnt){
	int i;

	if(x == y) return x;

	int p = lca(x, y);
	int q = p;

	if(x == p){
		int rem = depth1[y] - depth1[x] - 1;
		int z = y;
		for(i=17;i>=0;i--) if(rem >= (1<<i)){
			rem -= (1<<i);
			z = gparent[i][z];
		}
		if(count_child(z) != cnt / 2) return x;
		q = z;
	} else {
		if(count_child(x) != cnt / 2) return x;add_vertex
	}

	int a[] = {L[x], R[x], L[y], R[y], L[q], R[q]};
	REP(i,6){
		__typeof(ids.begin()) itr = ids.lower_bound(a[i]);
		int tmp = (*itr);

		if(tmp >= 0 && tmp < N){
			int z = center(x, y, order[tmp]);
			if(z != x) y = z;
		}
		itr--;
		tmp = (*itr);
		if(tmp >= 0 && tmp < N){
			int z = center(x, y, order[tmp]);
			if(z != x) y = z;
		}
	}

	return y;
}

int main(void){
	int i;

	cin >> N;
	for(i=1;i<N;i++){
		int p;
		scanf("%d%d", &p, &d[i]);
		p--;
		child[p].push_back(i);
		parent[i] = p;
	}

	dfs(0, 0, 0);
	prelca();
	ids.insert(-1);
	ids.insert(N+1);
	add_vertex
	ll sum = 0;
	int x = 0, y = 0;
	cout << 0 << endl;
	add_vertex(0);

	for(int z=1;z<N;z++){
		add_vertex(z);
		if(z % 2 == 0){
			x = center(x, y, z);
			sum += dist(x, z);
			printf(INT64 "\n", sum);
		} else {
			sum += dist(x, z);
			printf(INT64 "\n", sum);
			y = func(x, z, z+1);
		}
	}

	return 0;
}
