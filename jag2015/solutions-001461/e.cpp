#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// !!!  SHOULD AC !!!
// Problem: Cost Performance Flow
// Solution by: Michihiko Sawa
//
// O( (m log n) * n U ) : 多重辺なし
// O( (m log n) * m U ) : 多重辺あり
//
// implement 25 min
//
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;
typedef long long ll;
#define rep(i, n) for(int i = 0; i < static_cast<int>(n); ++i)
#define sz(v) (int)((v).size())
#define all(v) begin(v), end(v)

struct E{//{{{
    int s, t;
    ll cap, cost;
    int rev;
};//}}}
typedef vector<vector<E>> G;
void add_edge(G &g, int s, int t, ll cap, ll cost){//{{{
    if(s == t) return;
    int i = sz(g[s]), j = sz(g[t]);
    g[s].emplace_back(E{s, t, cap, cost, j});
    g[t].emplace_back(E{t, s,   0,-cost, i});
}//}}}

constexpr ll INF = numeric_limits<ll>::max();

// delta flow, delta cost
tuple<vector<ll>, vector<ll>> mcf(G &g, int src, int dst){//{{{
    const int n = sz(g);
    vector<ll> pot(n), dist;
    vector<E *> prev;
    ll flow = 0, cost = 0;
    vector<ll> flows, costs;
    while(true){//{{{
        dist.assign(n, INF);
        prev.assign(n, nullptr);
        priority_queue<tuple<ll, int>, vector<tuple<ll, int>>, greater<tuple<ll, int>>> pq;
        pq.emplace(dist[src] = 0, src);
        while(!pq.empty()){
            ll c; int u;
            tie(c, u) = pq.top(); pq.pop();
            if(c > dist[u]) continue;
            for(auto &e : g[u]) if(e.cap > 0){
                ll nc = c + e.cost + pot[e.s] - pot[e.t];
                if(nc < dist[e.t]){
                    pq.emplace(dist[e.t] = nc, e.t);
                    prev[e.t] = &e;
                }
            }
        }
        rep(u, n) if(dist[u] < INF) pot[u] += dist[u];
        E *e = prev[dst];
        if(e == nullptr) break;
        ll f = e->cap;
        for(; e != nullptr; e = prev[e->s]) f = min(f, e->cap);
        e = prev[dst];
        for(; e != nullptr; e = prev[e->s]){
            e->cap -= f;
            g[e->t][e->rev].cap += f;
        }
        flows.emplace_back(f);
        costs.emplace_back(pot[dst]);
        flow += f;
        cost += f * pot[dst];
    }//}}}
    return make_tuple(flows, costs);
}//}}}

int main(){//{{{
    int n, m;
    cin >> n >> m;
    G g(n);
    int src, dst;
    cin >> src >> dst; --src; --dst;
    rep(_, m){
        int s, t;
        ll cap, cost;
        cin >> s >> t >> cap >> cost;
        --s; --t;
        add_edge(g, s, t, cap, cost);
    }

    vector<ll> dxs, dys;
    tie(dxs, dys) = mcf(g, src, dst);
    const int T = sz(dxs);
    ll F = 0, C = 0;
    rep(i, T) F += dxs[i], C += dys[i] * dxs[i];

    reverse(all(dxs));
    reverse(all(dys));
    rep(i, T) dys[i] = -dys[i];

    ll x = 0, y = C;
    ll res = min(F*F, C*C);
    rep(i, T){//{{{
        ll t = dys[i];
        ll xx = x + dxs[i];
        ll yy = y + t * dxs[i];
        if(x + t * y < 0 and 0 < xx + t * yy){
            ll num = t * x - y;
            num *= num;
            ll den = 1 + t * t;
            ll g = llabs(__gcd(num, den));
            num /= g; den /= g;
            cout << num << '/' << den << endl;
            return 0;
        }
        res = min(res, x*x+y*y);
        x = xx; y = yy;
    }//}}}
    cout << res << '/' << 1 << endl;
    return 0;
}//}}}
// vim:set foldmethod=marker commentstring=//%s:
