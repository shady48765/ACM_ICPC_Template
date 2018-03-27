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
#define INF (1ll<<60)
ll ANS = INF;

int N;
int a[10];
bool exist[32];

void dfs(int pos){
	int i,j;
	
	if(pos == (1<<N)){
		ll tmp = 0;
		REP(i,(1<<N)) if(exist[i]) tmp++;
		
		bool failed = false;
		REP(i,N){
			int cnt = 0;
			REP(j,(1<<N)) if(j&(1<<i)) if(exist[j]) cnt++;
			if(cnt > a[i]) failed = true;
			tmp += a[i] - cnt;
		}
		
		if(!failed) ANS = min(ANS, tmp);
		
		return;
	}
	
	exist[pos] = false;
	dfs(pos+1);
	
	if(__builtin_popcount(pos) <= 1) return;
	REP(i,pos) if(exist[i] && __builtin_popcount(pos&i) >= 2) return;
	exist[pos] = true;
	dfs(pos+1);
}

int main(void){
	int i;
	
	cin >> N;
	REP(i,N) cin >> a[i];
	
	dfs(0);
	cout << ANS << endl;
	
	return 0;
}
