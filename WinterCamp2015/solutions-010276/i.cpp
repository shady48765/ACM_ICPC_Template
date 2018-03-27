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

typedef long long ll;
#define MOD 1000000007ll

#define MAXV 60

int parent[MAXV],rrank[MAXV];

void init(int n){
	int i;
	REP(i,n) {parent[i] = i; rrank[i] = 1;}
}

int root(int x){
	if(parent[x] != x) parent[x] = root(parent[x]);
	return parent[x];
}

void connect(int x, int y){
	int rx=root(x),ry=root(y);
	if(rx == ry) return;
	if(rrank[rx] > rrank[ry]) {parent[ry] = rx; rrank[rx] += rrank[ry];}
	if(rrank[rx] <= rrank[ry]) {parent[rx] = ry; rrank[ry] += rrank[rx];}
}

int N,M,A;
int s[60];

int getstr(ll mask){
	int i,j,k;
	
	init(M);
	REP(i,M) REP(j,M){
		int d = abs(i-j);
		if(mask&(1ll<<d)) connect(i, j);
	}
	
	int next = 0;
	REP(i,M){
		REP(j,i) if(root(j) == root(i)) break;
		if(j == i){
			s[i] = next;
			next++;
		} else {
			s[i] = s[j];
		}
	}
	
	return next;
}

ll dp[210];
ll dp2[210];

ll func(ll mask){
	int i,j;
	
	dp[0] = 1;
	for(i=1;i<=N;i++){
		if(i >= M){
			dp2[i] = dp[i-M];
			for(j=1;j<M;j++) if(mask&(1ll<<j)) dp2[i] = (dp2[i] - dp2[i-j] + MOD) % MOD;
		}
		dp[i] = (dp[i-1] * A - dp2[i] + MOD) % MOD;
	}
	
	ll ans = 1;
	REP(i,N) ans = ans * A % MOD;
	ans = (ans - dp[N] + MOD) % MOD;
	
	return ans;
}

bool check(int m, ll mask){ // cycles in [1, m) is mask
	int i,j;
	
	getstr(mask);
	for(i=1;i<m;i++) if(!(mask&(1ll<<i))){
		bool cycle = true;
		REP(j,M-i) if(s[j] != s[j+i]) cycle = false;
		if(cycle) return false;
	}
	
	return true;
}

vector <ll> masks;
ll cnt[3000];

void dfs(int pos, ll mask){
	if(pos == M){
		masks.push_back(mask);
		return;
	}
	if(check(pos+1, mask)) dfs(pos+1, mask);
	ll mask2 = (mask | (1ll<<pos));
	if(check(pos+1, mask2)) dfs(pos+1, mask2);
}

int main(void){
	int i,j;
	
	cin >> N >> M >> A;
	
	dfs(1, 0);
	int K = masks.size();
	
	ll ans = 0;
	
	for(i=K-1;i>=0;i--){
		int comp = getstr(masks[i]);
		cnt[i] = 1;
		REP(j,comp) cnt[i] = cnt[i] * A % MOD;
		for(j=i+1;j<K;j++) if((masks[i] & masks[j]) == masks[i]) cnt[i] = (cnt[i] - cnt[j] + MOD) % MOD;
		
		ll tmp = func(masks[i]);
		ans = (ans + cnt[i] * tmp) % MOD;
	}
	
	cout << ans << endl;
	
	return 0;
}
