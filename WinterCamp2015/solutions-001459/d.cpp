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
#define fi first
#define se second
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

typedef long double ld;

const int BL = 500;
const int MAXN = 200010;
const int MAXQ = 200010;

int par[MAXN], root[MAXN], froot[MAXN], occ[MAXN];
int part[MAXN], idles[MAXN];
int a[MAXN];

int N, Q;

int get_root(int x) {
    if (occ[x] || par[x] == -1) return x;
    if (root[x] != -1 || occ[x]) return root[x];
    return root[x] = get_root(par[x]);
}

int fast_get_root(int x) {
    x = get_root(x);
    if (par[x] == -1) return x;
    if (froot[x] != -1) return froot[x];
    return froot[x] = fast_get_root(par[x]);
}

int main() {
    ios::sync_with_stdio(false);

    freopen("1d-spreadsheet.in", "rt", stdin);
    freopen("1d-spreadsheet.out", "wt", stdout);


    cin >> N >> Q;
    forn(i, N) {
        cin >> a[i];
        par[i] = -1;
    }
    for (int q = 0; q < Q; q += BL) {
        int cq = min(Q - q, BL);
        vector<string> op(cq);
        vi x(cq), y(cq);
        forn(i, N) {
            occ[i] = 0;
            root[i] = -1;
        }
            
        forn(t, cq) {
            cin >> op[t] >> x[t] >> y[t];
            if (op[t] == "set") {
                --x[t];
                occ[x[t]] = 1;
            } else if (op[t] == "link") {
                --x[t];
                --y[t];
                occ[x[t]] = 1;
            } else {
                --x[t];
                --y[t];
            }
        }
        int K = 0;
        vi fr;
        forn(i, N) {
            if (occ[i]) {
                part[i] = K++;
                fr.pb(i);
            }
        }
//        int megasum = 0;
        vvi poss(K);
        forn(i, N + 1) idles[i] = 0;
        forn(i, N) {
            int r = get_root(i);
            if (occ[r]) {
                poss[part[r]].pb(i);
            } else idles[i + 1] = a[r];
        }
        forn(i, N) idles[i + 1] += idles[i];
        forn(t, cq) {
            if (op[t] == "set") {
                a[x[t]] = y[t];
                par[x[t]] = -1;
            } else if (op[t] == "link") {
                par[x[t]] = y[t];
                a[x[t]] = 0;
            } else {
                forn(i, K) froot[fr[i]] = -1;
                int result = idles[y[t] + 1] - idles[x[t]];
                forn(i, K) {
                    int r = fast_get_root(fr[i]);
                    int z = upper_bound(all(poss[i]), y[t]) - lower_bound(all(poss[i]), x[t]);
                    result += a[r] * z;
                }
                cout << result << '\n';
            }
        }
    }

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
