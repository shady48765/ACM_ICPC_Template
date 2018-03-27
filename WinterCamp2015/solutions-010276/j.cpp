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

int N,S;
int a[310];
ll dp[90010];

int main(void){
	int i,j;
	
	cin >> N;
	REP(i,N) cin >> a[i];
	cin >> S;
	
	dp[0] = 1;
	REP(i,N) for(j=90000;j>=0;j--) if(dp[j] != 0) dp[j+a[i]] = (dp[j+a[i]] - dp[j] + MOD) % MOD;
	
	ll ans = 0;
	REP(i,S){
		ll tmp = dp[i];
		REP(j,N) tmp = tmp * (S-i) % MOD;
		ans = (ans + tmp) % MOD;
	}
	
	cout << ans << endl;
	
	return 0;
}
