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
typedef pair<i64, i64> pi64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

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

#define sz(k) (1LL << (k))

int quarter(int K, pi64 p) {
    if (p.fi == sz(K) || p.se == sz(K)) return -1;
    return 2 * (p.se > sz(K)) + (p.fi > sz(K));
}

pi64 lower(int K, pi64 p) {
    assert(p.fi != sz(K) && p.se != sz(K));
    if (p.se > sz(K)) return mp(p.fi & (sz(K) - 1), p.se & (sz(K) - 1));
    if (p.fi < sz(K)) return mp(p.se, p.fi);
    return mp(p.se, sz(K + 1) - p.fi);
}

pi64 upper(int K, pi64 p, int q) {
    if (q == 0) return mp(p.se, p.fi);
    if (q == 1) return mp(sz(K + 1) - p.se, p.fi);
    if (q == 2) return mp(p.fi, p.se + sz(K));
    if (q == 3) return mp(p.fi + sz(K), p.se + sz(K));
    assert(false);
}

int skeleton_type(int K, pi64 p) {
    if (min(p.fi, p.se) == 0 || max(p.fi, p.se) == sz(K + 1)) return 1;
    return p.se > sz(K) ? 2 : 0;
}

i64 skeleton_dist(int K, pi64 p, pi64 q) {
    if (min(p.fi, q.fi) == 0 && max(p.fi, q.fi) == sz(K + 1)) return sz(K + 1) + min(p.se + q.se, 2 * sz(K + 1) - p.se - q.se);
    else if (min(p.se, q.se) == 0 && max(p.se, q.se) == sz(K + 1)) return sz(K + 1) + min(p.fi + q.fi, 2 * sz(K + 1) - p.fi - q.fi);
    return abs(p.fi - q.fi) + abs(p.se - q.se);
}

void moveTo(pi64 &p, pi64 q, i64 &cost) {
    cost += abs(p.fi - q.fi) + abs(p.se - q.se);
    p = q;
}

void pull(int K, pi64 &p, i64 &cost) {
    if (p.se == sz(K)) moveTo(p, mp(sz(K), 0), cost);
    else if (p.fi == sz(K)) moveTo(p, mp(sz(K), p.se < sz(K) ? 0 : 2 * sz(K)), cost);
}

pi64 escape(int K, pi64 p, i64 &cost) {
    if (p.fi != sz(K) && p.se != sz(K)) {
        p = upper(K, escape(K - 1, lower(K, p), cost), quarter(K, p));
    }
    pull(K, p, cost);
    return p;
}

bool pull2(int K, pi64 &p0, pi64 &p1, i64 &cost) {
    int q0 = quarter(K, p0), q1 = quarter(K, p1);
    if (q0 != -1 && q0 == q1) {
        p0 = lower(K, p0);
        p1 = lower(K, p1);
        if (pull2(K - 1, p0, p1, cost)) return true;
        p0 = upper(K, p0, q0);
        p1 = upper(K, p1, q1);
        q0 = q1 = -1; 
    }
    if (q0 != -1) p0 = upper(K, escape(K - 1, lower(K, p0), cost), q0);
    if (q1 != -1) p1 = upper(K, escape(K - 1, lower(K, p1), cost), q1);
    int t0 = skeleton_type(K, p0), t1 = skeleton_type(K, p1);
    if (t0 == 0 && t1 == 0 || t0 == 2 && t1 == 2) {
        moveTo(p0, p1, cost);
        return true;
    }
    pull(K, p0, cost);
    pull(K, p1, cost);
    assert(p0 != p1);
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "rt", stdin);
#else 
    freopen("hilbert.in", "rt", stdin);
    freopen("hilbert.out", "wt", stdout);
#endif

    int T;
//    cin >> T;
    scanf("%d", &T);
    while (T-->0) {
        int K, x0, y0, x1, y1;
//        cin >> K >> x0 >> y0 >> x1 >> y1;
        scanf("%d%d%d%d%d", &K, &x0, &y0, &x1, &y1);
        i64 cost = 0;
        pi64 p0 = mp((i64)x0, (i64)y0), p1 = mp((i64)x1, (i64)y1);
        if (!pull2(K, p0, p1, cost)) cost += skeleton_dist(K, p0, p1);
//        cout << cost << '\n';
        printf(INT64 "\n", cost);
//        printf(INT64 " %d %d %d %d\n", cost, x0, y0, x1, y1);
    }

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
