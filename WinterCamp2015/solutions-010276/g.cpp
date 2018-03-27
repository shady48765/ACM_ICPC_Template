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

int N;
ll x[1010],y[1010];

ll area(int p, int q, int r){
	return (x[q] - x[p]) * (y[r] - y[p]) - (x[r] - x[p]) * (y[q] - y[p]);
}

bool check(int p, int L, int R){
	int i;
	int q = L;
	for(i=L;i<R;i++) if(area(q, p, i) > 0) q = i;
	for(i=L;i<R;i++) if(area(q, p, i) > 0) return false;
	return true;
}

int main(void){
	int i;
	
	cin >> N;
	REP(i,N) cin >> x[i] >> y[i];
	
	bool ans = true;
	for(i=1;i<N;i++) if(!check(i, 0, i)) ans = false;
	for(i=N-1;i>=1;i--) if(!check(i-1, i, N)) ans = false;
	
	cout << (ans ? "Possible" : "Impossible") << endl;
	
	return 0;
}
