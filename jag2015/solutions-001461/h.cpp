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
//	hos
/*
	Problem: KimagureCleaner
	Solution by: hos
	
	O(2^((3/8)N) N)
		- check rectangles if (# of parts) <= THRESHOLD
		- separate x and y if (# of parts) >  THRESHOLD
	
	N <= 55, THRESHOLD := 39
*/

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <utility>
#include <numeric>
#include <algorithm>
#include <bitset>
#include <complex>
#include <cstdint>
#include <unordered_set>
#include <unordered_map>

using namespace std;

typedef long long Int;
typedef vector<int> vint;
typedef pair<int, int> pint;
#define mp make_pair

template <typename T1, typename T2> ostream &operator<<(ostream &os, const pair<T1, T2> &a) { return os << "(" << a.first << ", " << a.second << ")"; };
template <typename T> void pv(T a, T b) { for (T i = a; i != b; ++i) cout << *i << " "; cout << endl; }
template <typename T> void chmin(T &t, const T &f) { if (t > f) t = f; }
template <typename T> void chmax(T &t, const T &f) { if (t < f) t = f; }
int in() { int x; scanf("%d", &x); return x; }

const int LIM_N = 55;
const int THRESHOLD = 39;

struct Rect {
	Int xMin, xMax, yMin, yMax;
	Rect() : xMin(0), xMax(0), yMin(0), yMax(0) {}
	Rect(Int x, Int y) : xMin(x), xMax(x), yMin(y), yMax(y) {}
	Rect(Int xMin, Int xMax, Int yMin, Int yMax) : xMin(xMin), xMax(xMax), yMin(yMin), yMax(yMax) {}
	Rect operator+(const Rect &a) const { return Rect(xMin + a.xMin, xMax + a.xMax, yMin + a.yMin, yMax + a.yMax); }
	Rect operator-(const Rect &a) const { return Rect(xMin - a.xMax, xMax - a.xMin, yMin - a.yMax, yMax - a.yMin); }
	Rect operator+() const { return *this; }
	Rect operator-() const { return Rect() - *this; }
	Rect &operator+=(const Rect &a) { return *this = *this + a; }
	bool intersects(const Rect &a) const { return (xMax >= a.xMin && a.xMax >= xMin && yMax >= a.yMin && a.yMax >= yMin); }
};
ostream &operator<<(ostream &os, const Rect &a) {
	return os << "[" << a.xMin << "," << a.xMax << "]x[" << a.yMin << "," << a.yMax << "]";
}

int N;
Int X, Y;
char D[LIM_N + 10];
Int A[LIM_N + 10], B[LIM_N + 10];

int M;
int L[LIM_N + 10];
pint P[LIM_N + 10][LIM_N + 10];
Rect S[LIM_N + 10];
Rect R[LIM_N + 10];

int sigs[LIM_N + 10];
Int xs[LIM_N + 10], ys[LIM_N + 10];

void recover() {
// cout<<"recover"<<endl;
// cout<<"  sigs : ";pv(sigs,sigs+M);
	fill(xs, xs + N, 0);
	fill(ys, ys + N, 0);
	Int remX = X;
	Int remY = Y;
	for (int j = 0; j < M; ++j) {
		for (int l = 0; l < L[j]; ++l) {
			const int i = P[j][l].second;
			const Int tmpX = (sigs[j] ? -S[i] : +S[i]).xMin; remX -= tmpX; xs[i] += tmpX;
			const Int tmpY = (sigs[j] ? -S[i] : +S[i]).yMin; remY -= tmpY; ys[i] += tmpY;
		}
	}
	for (int j = 0; j < M; ++j) {
		for (int l = 0; l < L[j]; ++l) {
			const int i = P[j][l].second;
			const Int tmpX = min(remX, S[i].xMax - S[i].xMin); remX -= tmpX; xs[i] += tmpX;
			const Int tmpY = min(remY, S[i].yMax - S[i].yMin); remY -= tmpY; ys[i] += tmpY;
		}
	}
	assert(remX == 0);
	assert(remY == 0);
	for (int j = 1; j < M; ++j) {
		D[P[j][0].second] = (sigs[j - 1] != sigs[j]) ? 'R' : 'L';
	}
	printf("%d\n", N);
	for (int i = 0; i < N; ++i) {
		printf("%c " INT64 "\n", D[i], llabs(xs[i]) + llabs(ys[i]));
	}
}


namespace rect {

const int LIM_HALF = 20;

int sumsLens[2];
Rect sumss[2][(1 << LIM_HALF) + 10];

int ysLen;
Int ys[(1 << LIM_HALF) * 2 + 10];

inline int indexOf(Int y) {
	return upper_bound(ys, ys + ysLen, y) - ys;
}

int eventsLen;
pair<Int, pint> events[(1 << LIM_HALF) * 2 + 10];

int queriesLen;
pair<Int, int> queries[(1 << LIM_HALF) * 2 + 10];

int bitN;
Int bit0[(1 << LIM_HALF) * 2 + 10];
Int bit1[(1 << LIM_HALF) * 2 + 10];
//	[a, b)
void bitRangeAdd(int a, int b, Int val) {
	int x;
	for (x = max(a, 1); x <= bitN; x += x & -x) bit0[x] -= val * a, bit1[x] += val;
	for (x = max(b, 1); x <= bitN; x += x & -x) bit0[x] += val * b, bit1[x] -= val;
}
//	[0, a)
Int bitSum(int a) {
	Int sum0 = 0, sum1 = 0;
	int x;
	for (x = a; x > 0; x &= x - 1) sum0 += bit0[x], sum1 += bit1[x];
	return sum0 + sum1 * a;
}

bool run() {
	const int half = M / 2;
	sumsLens[0] = 1 << half;
	for (int h = 0; h < sumsLens[0]; ++h) {
		sumss[0][h] = R[0];
		for (int j = 1; j < 1 + half; ++j) {
			sumss[0][h] += (((h >> (j - 1)) & 1) ? -R[j] : +R[j]);
		}
	}
	sumsLens[1] = 1 << (M - 1 - half);
	for (int h = 0; h < sumsLens[1]; ++h) {
		sumss[1][h] = Rect();
		for (int j = 1 + half; j < M; ++j) {
			sumss[1][h] += (((h >> (j - 1 - half)) & 1) ? -R[j] : +R[j]);
		}
		sumss[1][h] = Rect(X, Y) - sumss[1][h];
	}
// for(int s=0;s<2;++s){cout<<"sumss["<<s<<"] : ";pv(sumss[s],sumss[s]+sumsLens[s]);}
	for (int s = 0; s < 2; ++s) {
		ysLen = 0;
		for (int h = 0; h < sumsLens[s]; ++h) {
			ys[ysLen++] = sumss[s][h].yMin;
			ys[ysLen++] = sumss[s][h].yMax + 1;
		}
		sort(ys, ys + ysLen);
		ysLen = unique(ys, ys + ysLen) - ys;
		eventsLen = 0;
		for (int h = 0; h < sumsLens[s]; ++h) {
			events[eventsLen++] = mp(sumss[s][h].xMin    , mp(+1, h));
			events[eventsLen++] = mp(sumss[s][h].xMax + 1, mp(-1, h));
		}
		sort(events, events + eventsLen);
		queriesLen = 0;
		for (int h = 0; h < sumsLens[s ^ 1]; ++h) {
			queries[queriesLen++] = mp(sumss[s ^ 1][h].xMin, h);
			queries[queriesLen++] = mp(sumss[s ^ 1][h].xMax, h);
		}
		sort(queries, queries + queriesLen);
		bitN = ysLen;
		fill(bit0, bit0 + bitN + 1, 0);
		fill(bit1, bit1 + bitN + 1, 0);
		for (int e = 0, q = 0; q < queriesLen; ++q) {
			for (; e < eventsLen && events[e].first <= queries[q].first; ++e) {
				const int he = events[e].second.second;
				bitRangeAdd(indexOf(sumss[s][he].yMin), indexOf(sumss[s][he].yMax + 1), events[e].second.first);
			}
			const int hq = queries[q].second;
			if (bitSum(indexOf(sumss[s ^ 1][hq].yMax + 1)) - bitSum(indexOf(sumss[s ^ 1][hq].yMin)) > 0) {
				for (int h = 0; h < sumsLens[s]; ++h) {
					if (sumss[s][h].intersects(sumss[s ^ 1][hq])) {
// cout<<"s = "<<s<<", h = "<<h<<", hq = "<<hq<<endl;
						const int h0 = (s == 0) ? h : hq;
						const int h1 = (s == 0) ? hq : h;
						for (int j = 1; j < 1 + half; ++j) {
							sigs[j] = (h0 >> (j - 1)) & 1;
						}
						for (int j = 1 + half; j < M; ++j) {
							sigs[j] = (h1 >> (j - 1 - half)) & 1;
						}
						return true;
					}
				}
				assert(false);
			}
		}
	}
	return false;
}

}	//	namespace rect


namespace sep {

const int LIM_HALF = 14;

struct Inter {
	Int Min, Max;
	Inter() : Min(0), Max(0) {}
	explicit Inter(Int x) : Min(x), Max(x) {}
	Inter(Int Min, Int Max) : Min(Min), Max(Max) {}
	Inter operator+(const Inter &a) const { return Inter(Min + a.Min, Max + a.Max); }
	Inter operator-(const Inter &a) const { return Inter(Min - a.Max, Max - a.Min); }
	Inter operator+() const { return *this; }
	Inter operator-() const { return Inter() - *this; }
	Inter &operator+=(const Inter &a) { return *this = *this + a; }
	bool intersects(const Inter &a) const { return (Max >= a.Min && a.Max >= Min); }
};
ostream &operator<<(ostream &os, const Inter &a) {
	return os << "[" << a.Min << "," << a.Max << "]";
}

int sumsLens[2];
Inter sumss[2][(1 << LIM_HALF) + 10];

int eventsLen;
pair<Int, int> events[(1 << LIM_HALF) * 2 + 10];

int queriesLen;
pair<Int, int> queries[(1 << LIM_HALF) * 2 + 10];

int runOneDim(const Inter &base, Int target, int intersLen, const pair<Inter, int> inters[]) {
// cout<<"runOneDim"<<endl;
// cout<<"  base = "<<base<<", target = "<<target<<endl;
// cout<<"  inters : ";pv(inters,inters+intersLen);
	const int half = intersLen / 2;
	sumsLens[0] = 1 << half;
	for (int h = 0; h < sumsLens[0]; ++h) {
		sumss[0][h] = base;
		for (int k = 0; k < half; ++k) {
			sumss[0][h] += (((h >> k) & 1) ? -inters[k].first : +inters[k].first);
		}
	}
	sumsLens[1] = 1 << (intersLen - half);
	for (int h = 0; h < sumsLens[1]; ++h) {
		sumss[1][h] = Inter();
		for (int k = half; k < intersLen; ++k) {
			sumss[1][h] += (((h >> (k - half)) & 1) ? -inters[k].first : +inters[k].first);
		}
		sumss[1][h] = Inter(target) - sumss[1][h];
	}
// for(int s=0;s<2;++s){cout<<"sumss["<<s<<"] : ";pv(sumss[s],sumss[s]+sumsLens[s]);}
	for (int s = 0; s < 2; ++s) {
		eventsLen = 0;
		for (int h = 0; h < sumsLens[s]; ++h) {
			events[eventsLen++] = mp(sumss[s][h].Min    , +1);
			events[eventsLen++] = mp(sumss[s][h].Max + 1, -1);
		}
		sort(events, events + eventsLen);
		queriesLen = 0;
		for (int h = 0; h < sumsLens[s ^ 1]; ++h) {
			queries[queriesLen++] = mp(sumss[s ^ 1][h].Min, h);
			queries[queriesLen++] = mp(sumss[s ^ 1][h].Max, h);
		}
		sort(queries, queries + queriesLen);
		int now = 0;
		for (int e = 0, q = 0; q < queriesLen; ++q) {
			for (; e < eventsLen && events[e].first <= queries[q].first; ++e) {
				now += events[e].second;
			}
			if (now > 0) {
				const int hq = queries[q].second;
				for (int h = 0; h < sumsLens[s]; ++h) {
					if (sumss[s][h].intersects(sumss[s ^ 1][hq])) {
// cout<<"s = "<<s<<", h = "<<h<<", hq = "<<hq<<endl;
						const int h0 = (s == 0) ? h : hq;
						const int h1 = (s == 0) ? hq : h;
						return h0 | h1 << half;
					}
				}
				assert(false);
			}
		}
	}
	return -1;
}

int heaviesLen;
int heavies[LIM_N + 10];

int psLen, qsLen;
pair<Inter, int> ps[LIM_N + 10], qs[LIM_N + 10];

bool run() {
	heaviesLen = 0;
	for (int j = 1; j < M; ++j) if (L[j] > 1) {
		heavies[heaviesLen++] = j;
	}
	psLen = 0;
	qsLen = 0;
	for (int j = 1; j < M; ++j) if (L[j] == 1) {
		if (R[j].yMin == 0 && R[j].yMax == 0) {
			ps[psLen++] = mp(Inter(R[j].xMin, R[j].xMax), j);
		} else if (R[j].xMin == 0 && R[j].xMax == 0) {
			qs[qsLen++] = mp(Inter(R[j].yMin, R[j].yMax), j);
		} else {
			assert(false);
		}
	}
	for (int g = 0; g < 1 << heaviesLen; ++g) {
		for (int k = 0; k < heaviesLen; ++k) {
			sigs[heavies[k]] = (g >> k) & 1;
		}
		Rect r0 = R[0];
		for (int j = 1; j < M; ++j) if (L[j] > 1) {
			r0 += (sigs[j] ? -R[j] : +R[j]);
		}
		const int resX = runOneDim(Inter(r0.xMin, r0.xMax), X, psLen, ps);
		const int resY = runOneDim(Inter(r0.yMin, r0.yMax), Y, qsLen, qs);
		if (resX != -1 && resY != -1) {
			for (int k = 0; k < psLen; ++k) {
				sigs[ps[k].second] = (resX >> k) & 1;
			}
			for (int k = 0; k < qsLen; ++k) {
				sigs[qs[k].second] = (resY >> k) & 1;
			}
			return true;
		}
	}
	return false;
}

}	//	sep


bool solve() {
	D[N] = '?';
	A[N] = B[N] = 0;
	M = 0;
	fill(L, L + N, 0);
	int dir = 0;
	for (int i = 0; i <= N; ++i) {
		if (D[i] == '?') {
			++M;
		}
		if (D[i] == 'R') {
			--dir &= 3;
		} else {
			++dir &= 3;
		}
		P[M][L[M]++] = mp(dir, i);
	}
// cout<<"M = "<<M<<endl;
// cout<<"L : ";pv(L,L+M);
// for(int j=0;j<M;++j){cout<<"  P["<<j<<"] : ";pv(P[j],P[j]+L[j]);}
	for (int j = 0; j < M; ++j) {
		R[j] = Rect();
		for (int l = 0; l < L[j]; ++l) {
			const int i = P[j][l].second;
			switch (P[j][l].first) {
				case 0: S[i] = Rect(+A[i], +B[i], 0, 0); break;
				case 1: S[i] = Rect(0, 0, +A[i], +B[i]); break;
				case 2: S[i] = Rect(-B[i], -A[i], 0, 0); break;
				case 3: S[i] = Rect(0, 0, -B[i], -A[i]); break;
				default: assert(false);
			}
			R[j] += S[i];
		}
	}
// cout<<"R : ";pv(R,R+M);
	if (M <= THRESHOLD) {
		return rect::run();
	} else {
		return sep::run();
	}
}

int main() {
	
	
	for (; ~scanf("%d" INT64 "" INT64, &N, &X, &Y); ) {
		for (int i = 0; i < N; ++i) {
			scanf(" %c" INT64 "" INT64, &D[i], &A[i], &B[i]);
		}
		const bool res = solve();
		if (res) {
			recover();
		} else {
			puts("-1");
		}
	}
	
	return 0;
}

