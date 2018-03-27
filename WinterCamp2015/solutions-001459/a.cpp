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

struct TEdge {
    int from, to;
    i64 c, ocost, cost, w;

    TEdge(int from = 0, int to = 0, i64 c = 0, i64 cost = 0)
        : from(from)
        , to(to)
        , c(c)
        , ocost(cost)
        , cost(cost)
        , w(0)
    {
    }
};

const int MAXN = 1110;
const int MAXM = 1110 * 1110;
const i64 INF = 1e18;

vi e[MAXN];
TEdge edges[2 * MAXM];
int ec = 0;

void addEdge(int from, int to, i64 c, i64 cost) {
    if (c <= 0) return;
    e[from].pb(ec);
    edges[ec++] = TEdge(from, to, c, cost);
    e[to].pb(ec);
    edges[ec++] = TEdge(to, from, 0, -cost);
}

i64 dist[MAXN], vis[MAXN], par[MAXN], pushed[MAXN];
i64 pot[MAXN];

void init(int N) {
    forn(i, N) {
        dist[i] = INF;
        vis[i] = 0;
        par[i] = -1;
        pushed[i] = 0;
    }
}

void reduceCost() {
    forn(i, ec) {
        if (edges[i].w < edges[i].c) {
            edges[i].cost += dist[edges[i].from] - dist[edges[i].to];
            edges[i ^ 1].cost = 0;
        }
    }
}

int push(int from, int to, int N) {
    init(N);
    dist[from] = 0;
    pushed[from] = INF;
    set<pii> q;
    q.insert(mp(dist[from], from));
    while (!q.empty()) {
        int m = q.begin()->se;
        q.erase(q.begin());
        vis[m] = 1;  
        //for (int id: e[m]) {
        forn(j, e[m].size()) {
            int id = e[m][j];
            if (edges[id].w >= edges[id].c) continue;
            int to = edges[id].to;
            int w = edges[id].cost;
            if (dist[m] + w < dist[to]) {
                q.erase(mp(dist[to], to));
                dist[to] = dist[m] + w;
                q.insert(mp(dist[to], to));
                par[to] = id;
                pushed[to] = min(pushed[m], edges[id].c - edges[id].w);
            }
        }
    }
    reduceCost();
    if (!pushed[to]) return 0;
    int pt = pushed[to];
    int v = to;
    while (par[v] != -1) {
        int id = par[v];
        edges[id].w += pt;
        edges[id ^ 1].w -= pt;
        v = edges[id].from;
    }
    return pt;
}

void maxflow_mincost(int from, int to, int N) {
    init(N);
    dist[from] = 0;
    bool changed;
    do {
        changed = false;
        forn(i, ec) {
            if (edges[i].w >= edges[i].c) continue;
            changed |= uin(dist[edges[i].to], dist[edges[i].from] + edges[i].cost);
        }
    } while (changed);
    reduceCost();
    while (push(from, to, N)) {}
}

i64 h[1111];

int main() {
    ios::sync_with_stdio(false);
//    cin.tie(nullptr);
    cout.precision(10);
    cout << fixed;
#ifdef LOCAL_DEFINE
    freopen("input.txt", "rt", stdin);
#else
    freopen("aarelia.in", "rt", stdin);
    freopen("aarelia.out", "wt", stdout);
#endif

    int N, M;
    cin >> N >> M;
    forn(i, N) cin >> h[i + 1];
    h[0] = -INF / 2;
    h[N + 1] = INF / 2;
    int S = N + 1, T = N + 2;
    int need = 0;
    forn(i, N + 1) {
        if (h[i] < h[i + 1]) {
            addEdge(S, i, h[i + 1] - h[i], 0);
        }
        if (h[i] > h[i + 1]) {
            addEdge(i, T, h[i] - h[i + 1], 0);
            need += h[i] - h[i + 1];
        }
    }
    forn(i, M) {
        char op;
        int l, c;
        cin >> op >> l >> c;
        for (int j = 0; j + l <= N; ++j) {
            if (op == '+') addEdge(j + l, j, INF, c);
            else addEdge(j, j + l, INF, c);
        }
    }
    maxflow_mincost(S, T, T + 1);
    int flow = 0;
    forn(i, e[S].size()) flow += edges[e[S][i]].w;
    if (flow < need) {
        cout << -1 << '\n';
        return 0;
    }
    i64 cost = 0;
    forn(i, T + 1) forn(j, e[i].size()) {
        int w = e[i][j];
//        cerr << edges[w].from << ' ' << edges[w].to << ' ' << edges[w].w << ' ' << edges[w].c << ' ' << edges[w].ocost << '\n';
        cost += max(0LL, edges[w].w) * edges[w].ocost;
    }
    cout << cost << '\n';

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
