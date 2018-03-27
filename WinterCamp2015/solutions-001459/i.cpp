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

const i64 P = 1000000000 + 7;

i64 deg(i64 x, i64 d) {
    d %= P - 1;
    if (d < 0) d += P - 1;
    i64 res = 1;
    while (d) {
        if (d & 1) {
            res *= x; res %= P;
        }
        x *= x; x %= P;
        d /= 2;
    }
    return res;
}

i64 inv(i64 x) {
    return deg(x, P - 2);
}

void add(i64 &x, i64 y) {
    x += y;
    x %= P; if (x < 0) x += P;
}

const int MAXN = 3000;

i64 coef[2 * MAXN][MAXN];
vi e[2 * MAXN];
i64 h[2 * MAXN];
int w[2 * MAXN];

void dfs(int v) {
    if (e[v].empty()) {
        coef[v][0] = deg(2, -h[v]);
        w[v] = 1;
        return;
    }
    int u1 = e[v][0], u2 = e[v][1];
    dfs(u1); dfs(u2);
    w[v] = w[u1] + w[u2];
    h[v] = max(h[u1], h[u2]) + 1;
    forn(i, w[u1]) forn(j, w[u2]) {
        i64 z = coef[u1][i] * coef[u2][j] % P;
        i64 den = inv(deg(2, i + j + 1) - 1);
        z *= den; z %= P;
        z *= (P + 1) / 2; z %= P;
        add(coef[v][i + j + 1], z);
        add(coef[v][0], -z * deg(2, (h[v] - 1) * (i + j + 1)));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "rt", stdin);
#else
    freopen("infinite.in", "rt", stdin);
    freopen("infinite.out", "wt", stdout);
#endif

    int N;
    cin >> N;
    forn(i, N) {
        int t;
        cin >> t;
        if (t == 0) {
            forn(j, 2) {
                int x;
                cin >> x;
                --x; e[i].pb(x);
            }
        } else {
            cin >> h[i];
            h[i] *= -1;
        }
    }
    int root = 0;
    while (1) {
        bool ok = true;
        forn(i, N) forn(j, e[i].size()) if (e[i][j] == root) {
            ok = false;
            break;
        }
        if (ok) break;
        ++root;
    }
    dfs(root);
    i64 ans = 0;
    if (h[root] <= 0) {
        forn(i, w[root]) add(ans, coef[root][i]);
    }
    cout << ans << '\n';

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
