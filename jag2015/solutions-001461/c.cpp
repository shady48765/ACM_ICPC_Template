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
	Problem: Casino
	Solution by: hos
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

const int LIM_OUTPUT = 100;
const int LIM_E = 10000;	//	0.99^LIM_E : small enough

typedef long double Double;

void allMoves(Int lim) {
	printf(INT64 "\n", lim);
	int ou = 0;
	if (lim > LIM_OUTPUT + LIM_OUTPUT) {
		for (Int d = 1; d <= LIM_OUTPUT; ++d) {
			if (ou++) {
				printf(" ");
			}
			printf(INT64, d);
		}
		for (Int d = lim - LIM_OUTPUT + 1; d <= lim; ++d) {
			if (ou++) {
				printf(" ");
			}
			printf(INT64, d);
		}
	} else {
		for (Int d = 1; d <= lim; ++d) {
			if (ou++) {
				printf(" ");
			}
			printf(INT64, d);
		}
	}
	puts("");
}

Double P, R;
Int M, N;

int main() {
	
	
	for (; ~scanf("%Lf" INT64 "" INT64, &P, &M, &N); ) {
		P /= 100.0;
cerr<<"P = "<<P<<", M = "<<M<<", N = "<<N<<endl;
		if (P == 0.0) {
			puts("0");
			allMoves(M);
		} else if (0.0 < P && P < 0.5) {
			R = (1.0 - P) / P;
			vector<Double> summands;
			vector<Int> candidates;
			Int m = M;
			Double t = 1.0;
			for (int e = 0; e < LIM_E; ++e) {
				if (m >= N) {
					m -= N;
					summands.push_back(t);
					t *= R;
				} else {
					if (m << 1 >= N) {
						for (const Int l : { m, N - m }) {
							if (__builtin_ctzll(l) >= e) {
								const Int d = l >> e;
								if (1 <= d && d <= min(M, N - M)) {
									candidates.push_back(d);
								}
							}
						}
					}
				}
				m <<= 1;
				t /= (R + 1.0);
			}
			sort(summands.begin(), summands.end());
			sort(candidates.begin(), candidates.end());
			candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
			printf("%.12Lf\n", accumulate(summands.begin(), summands.end(), 0.0L));
			const int sz = candidates.size();
			printf("%d\n", sz);
			int ou = 0;
			for (int i = 0; i < sz; ++i) if (i < LIM_OUTPUT || sz - LIM_OUTPUT <= i) {
				if (ou++) {
					printf(" ");
				}
				printf(INT64, candidates[i]);
			}
			puts("");
		} else if (P == 0.5) {
			printf("%.12Lf\n", (Double)M / N);
			allMoves(min(M, N - M));
		} else if (0.5 < P && P < 1.0) {
			R = (1.0 - P) / P;
			printf("%.12Lf\n", (1.0 - pow(R, M)) / (1.0 - pow(R, N)));
			puts("1");
			puts("1");
		} else if (P == 1.0) {
			puts("1");
			allMoves(M);
		} else {
			assert(false);
		}
	}
	
	return 0;
}

