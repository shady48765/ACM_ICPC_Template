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

int a[500010],b[500010],p[500010];

int gcd(int x, int y){
	return x ? gcd(y%x, x) : y;
}

map <pair <int, int>, int> mp;
vector <ll> opposite;

struct point {ll x,y,cost;};

bool operator<(const point &P, const point &Q){
	bool Pbig = (P.y < 0 || (P.y == 0 && P.x < 0));
	bool Qbig = (Q.y < 0 || (Q.y == 0 && Q.x < 0));
	if(Pbig != Qbig) return Qbig;
	return (P.x * Q.y > P.y * Q.x);
}

point P[500010];

ll area(int p, int q, int N){
	p %= N;
	q %= N;
	return P[p].x * P[q].y - P[p].y * P[q].x;
}

ll func(int N, int p){
	int q,r=p+1;
	ll ans = INF;
	ll best = INF;
	
	for(q=p+1;q<p+N;q++){
		while(r+1 < p+N && area(q, r+1, N) > 0){
			r++;
			if(area(p, r, N) < 0) best = min(best, P[r%N].cost);
		}
		if(area(p, q, N) > 0) ans = min(ans, P[p].cost + P[q%N].cost + best);
	}
	
	return ans;
}

int main(void){
	int N,i;
	
	cin >> N;
	REP(i,N) scanf("%d%d%d", &a[i], &b[i], &p[i]);
	
	REP(i,N){
		int g = gcd(abs(a[i]), abs(b[i]));
		if(g != 0){
			pair <int, int> tmp = make_pair(a[i]/g, b[i]/g);
			if(mp.find(tmp) == mp.end() || p[i] < mp[tmp]) mp[tmp] = p[i];
		}
	}
	
	snuke(mp,itr){
		pair <int, int> tmp = (itr->first);
		if(tmp > make_pair(0, 0)){
			pair <int, int> pmt = make_pair(-tmp.first, -tmp.second);
			if(mp.find(pmt) != mp.end()) opposite.push_back((ll)(itr->second) + mp[pmt]);
		}
	}
	
	ll ans = INF;
	
	if(opposite.size() >= 2){
		sort(opposite.begin(),opposite.end());
		ans = opposite[0] + opposite[1];
	}
	
	N = 0;
	snuke(mp,itr){
		P[N].x = (itr->first).first;
		P[N].y = (itr->first).second;
		P[N].cost = (itr->second);
		N++;
	}
	
	sort(P, P+N);
	
	int cheap = 0;
	REP(i,N) if(P[i].cost < P[cheap].cost) cheap = i;
	REP(i,N) if(i == cheap || (P[i].x == -P[cheap].x && P[i].y == -P[cheap].y)){
		ll tmp = func(N, i);
		ans = min(ans, tmp);
	}
	
	if(ans == INF) ans = -1;
	cout << ans << endl;
	
	return 0;
}
