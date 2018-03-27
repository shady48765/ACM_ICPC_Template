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

#define MAX (1<<9)
#define INF (1<<29)

int W,N;
string input;

int pre;
int s[MAX];

int E;
int a[2100],b[2100],c[2100]; // pot[b[i]] - pot[a[i]] <= c[i]
int dp[MAX];

bool check(void){
	int i,j,k;
	
	E = 0;
	REP(i,N) REP(j,2){
		int from = i;
		int to = i / 2 + (j<<(2*W));
		// pot[to] - pot[from] = s[to] - j
		a[E] = from;
		b[E] = to;
		c[E] = ((to < pre) ? s[to] : 1) - j;
		E++;
		// pot[from] - pot[to] = j - s[to]
		a[E] = to;
		b[E] = from;
		c[E] = j - ((to < pre) ? s[to] : 0);
		E++;
	}
	
	REP(i,MAX) dp[i] = 0;
	REP(i,MAX+5) REP(j,E){
		dp[b[j]] = min(dp[b[j]], dp[a[j]] + c[j]);
		if(dp[b[j]] < -INF) return false;
	}
	REP(j,E) if(dp[a[j]] + c[j] < dp[b[j]]) return false;
	
	return true;
}

int main(void){
	int i;
	
	cin >> W >> input;
	N = input.length();
	
	REP(i,N) s[i] = input[i] - '0';
	pre = N;
	if(check()){
		cout << input << endl;
		return 0;
	}
	
	for(i=N-1;i>=0;i--) if(s[i] == 0){
		s[i] = 1;
		pre = i + 1;
		if(check()) break;
	}
	
	if(i == -1){
		cout << "no" << endl;
		return 0;
	}
	
	while(pre < N){
		s[pre] = 0;
		pre++;
		if(!check()) s[pre-1]++;
	}
	
	string ans;
	REP(i,N) ans += (char)('0' + s[i]);
	cout << ans << endl;
	
	return 0;
}
