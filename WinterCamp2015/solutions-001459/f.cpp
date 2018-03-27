#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <numeric>

#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define ford(i, n) for (int i = (int)((n) - 1); i >= 0; --i)
#define fornn(i, a, b) for (int i = (int)(a); i < (int)(b); ++i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)
#define debugv(a) forn(i, a.size()) cerr << a[i] << ' '; cerr << '\n'

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;

typedef long long i64;
typedef pair<i64, i64> pi64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

const int MAXN = 1000010;
const i64 P = 1000000000 + 7;
i64 ma2[2], mpa2[2];
i64 ms2[2], msj2[2];
i64 ma[2], mpa[2];
                                                     
int inverse(int x) {
    int res = 1;
    int d = P - 2;
    while (d) {
        if (d & 1) {
            res = (1LL * res * x) % P;
        }
        d >>= 1;
        x = (1LL * x * x) % P;
    }
    return res;
}

int main() {
    freopen("fibonacci.in", "rt", stdin);
    freopen("fibonacci.out", "wt", stdout);

    int N, K;
    cin >> N;
    K = 2;
    ma[0] = mpa[1] = 1;
    ma2[0] = mpa2[1] = 1;
    ms2[1] = 1;
    for (int i = 1; i <= N; ++i) {
        i64 invi = inverse(i);
        int t = i & 1, tt = t ^ 1;
        ma[t] = K * invi % P * mpa[t] % P;
        mpa[tt] = (mpa[t] + ma[t]) % P;

        ma2[t] = K * (i + K - 1) % P * invi % P * invi % P * mpa2[t];
        ma2[t] += 2LL * K * K % P * (K - 1) % P * invi % P * invi % P * msj2[t];
        ma2[t] %= P;

        mpa2[tt] = (mpa2[t] + ma2[t]) % P;
        msj2[tt] = (msj2[t] + invi * ms2[t]) % P;
        ms2[tt] = (mpa2[tt] + 2 * K * msj2[tt]) % P;
    }
    cout.precision(10);
    cout << fixed;
    cout << (ma2[N & 1] + P - ma[N & 1] * ma[N & 1] % P) % P << '\n';

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
