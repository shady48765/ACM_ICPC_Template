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

int N;
string s[60];
ll dp[30][30][60][60];

ll func(int pos, int next, int L, int R){
	int i;
	
	if(next == 27) return dp[pos][next][L][R] = 0;
	if(pos == 20) return dp[pos][next][L][R] = ((R-L == 1) ? 1 : 0);
	if(dp[pos][next][L][R] != -1) return dp[pos][next][L][R];
	
	ll ans = func(pos, next+1, L, R);
	for(int M=L+1;M<=R;M++){
		if(s[M-1][pos] == '?' && next == 0) break;
		if(s[M-1][pos] != '?' && next != s[M-1][pos] - 'a' + 1) break;
		ll tmp = func(pos+1, 0, L, M);
		if(M < R) tmp = tmp * func(pos, next+1, M, R) % MOD;
		ans = (ans + tmp) % MOD;
	}
	
	return dp[pos][next][L][R] = ans;
}

int main(void){
	int i,j,k,l;
	
	cin >> N;
	REP(i,N) cin >> s[i];
	
	char small = 'a';
	small--;
	REP(i,N) while(s[i].length() < 20) s[i] += small;
	
	REP(i,30) REP(j,30) REP(k,60) REP(l,60) dp[i][j][k][l] = -1;
	
	ll ans = func(0, 0, 0, N);
	cout << ans << endl;
	
	return 0;
}
