#include <iostream>
#include <vector>
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
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;
typedef long double ld;

template<class T>
bool uin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template<class T>
bool uax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

const int MAXN = 200000;
int x[MAXN], m[MAXN];

const ld EPS = 1e-11;

struct TEvent {
    ld x, a, b, c;

    TEvent(ld x = 0, ld a = 0, ld b = 0, ld c = 0)
        : x(x)
        , a(a)
        , b(b)
        , c(c)
    {
    }

    bool operator<(const TEvent &ev) const {
        if (fabs(x - ev.x) > EPS) return x < ev.x;
        return false;
    }
};

int N;
ld L, T, E;

ld clamp(ld x, ld d) {
    return min(L - d, max(x, d));
}

int main() {
    ios::sync_with_stdio(false);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "rt", stdin);
#else
    freopen("barduck.in", "rt", stdin);
    freopen("barduck.out", "wt", stdout);
#endif

//    cin >> N >> L >> T >> E;
//    forn(i, N) cin >> x[i] >> m[i];
    double _l, _t, _e;
    scanf("%d%lf%lf%lf", &N, &_l, &_t, &_e);
    L = _l; T = _t; E = _e;
    forn(i, N) scanf("%d%d", &x[i], &m[i]);
    E *= 2 * T * T;

    ld l = 0.0, r = 0.5 * L;
    ld cent = 0;
    forn(its, 100) {
        ld d = 0.5 * (l + r);
        vector<TEvent> evs;
        int i1 = 0, i2 = 0, i3 = 0;
        evs.pb(TEvent(d, 0, 0, 0));
        while (i1 < N || i2 < N || i3 < N) {
//            cerr << i1 << ' ' << i2 << ' ' << i3 << '\n';
            ld x1 = (i1 < N ? x[i1] - d : 2e9);
            ld x2 = (i2 < N ? x[i2] : 2e9);
            ld x3 = (i3 < N ? x[i3] + d : 2e9);
            if (min(x1, min(x2, x3)) > 1e9) break;
            if (x1 < x2 + EPS && x1 < x3 + EPS) {
                evs.pb(TEvent(clamp(x1, d), m[i1], -2 * m[i1] * x1, m[i1] * x1 * x1));
                ++i1;
            } else if (x2 < x1 + EPS && x2 < x3 + EPS) {
                evs.pb(TEvent(clamp(x2, d), 0, -4 * m[i2] * d, 4 * m[i2] * d * x2));
                ++i2;
            } else {
                evs.pb(TEvent(clamp(x3, d), -m[i3], 2 * m[i3] * x3, -m[i3] * x3 * x3));
                ++i3;
            }
        }
        evs.pb(TEvent(L - d, 0, 0, 0));
        ld res = 1e19;
        ld a = 0, b = 0, c = 0;
        int i = 0;
        while (1) {
            ld x = evs[i].x;
            while (i < evs.size() && fabs(evs[i].x - x) < EPS) {
                a += evs[i].a;
                b += evs[i].b;
                c += evs[i].c;
                ++i;
            }
            if (i == evs.size()) break;
            ld xx = evs[i].x;
            if (uin(res, a * x * x + b * x + c)) cent = x;
            if (uin(res, a * xx * xx + b * xx + c)) cent = xx;
            if (fabs(a) > EPS) {
                ld t = -0.5 * b / a;
                if (x < t && t < xx) if (uin(res, a * t * t + b * t + c)) cent = t;
            }
        }
        cerr << l << ' ' << res << '\n';
        if (res < E) l = d;
        else r = d;
    }

    cout << 2 * (double)l << '\n';

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
