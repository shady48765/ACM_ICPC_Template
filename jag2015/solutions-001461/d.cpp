#include <stdlib.h>
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
//
// Problem: Content Delivery
// Solution by: MORI Shingo
// O(n^2logn)
//
// implement 25min
// 
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <assert.h>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <set>

using namespace std;
typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;
static const double EPS = 1e-9;
static const double PI = acos(-1.0);

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))

typedef ll Weight;
struct Edge {
  int src;
  int dest;
  Weight weight;
  Edge(int src, int dest, Weight weight) : src(src), dest(dest), weight(weight) {;}
  bool operator<(const Edge &rhs) const {
    if (weight != rhs.weight) { return weight > rhs.weight; }
    if (src != rhs.src) { return src < rhs.src; }
    return dest < rhs.dest;
  }
};
typedef vector<Edge> Edges;
typedef vector<Edges> Graph;
typedef vector<Weight> Array;
typedef vector<Array> Matrix;

struct Input {
  int n, m;
  Graph g;
  vector<ll> s;
};

namespace Solver {
  ll dfs(const Graph &g, int from, int parent, ll w, vector<ll> &costs) {
    ll max_dist = 0;
    FORIT(it, g[from]) {
      int to = it->dest;
      if (parent == to) { continue; }
      ll nd = dfs(g, to, from, w, costs) + it->weight * w;
      if (nd > max_dist) {
        if (max_dist != 0) { costs.push_back(max_dist); }
        max_dist = nd;
      } else {
        costs.push_back(nd);
      }
    }
    return max_dist;
  }

  vector<ll> CalcCosts(const Graph &g, const vector<ll> &s) {
    const int n = g.size();
    vector<ll> costs;

    REP(root, n) {
      ll d = dfs(g, root, root, s[root], costs);
      costs.push_back(d);
    }

    sort(costs.rbegin(), costs.rend());
    return costs;
  }

  ll Main(const Input &input) {
    vector<ll> costs = CalcCosts(input.g, input.s);
    int m = min(input.m, (int)costs.size());
    ll ans = 0;
    REP(i, m) {
      ans += costs[i];
    }
    return ans;
  }
}

int main() {
  Input input;
  while (scanf("%d %d", &input.n, &input.m) > 0 && input.n > 0) {
    int n = input.n;
    input.g = Graph(n);
    input.s = vector<ll>(n, 0);
    REP(i, n - 1) {
      int f, t;
      ll c;
      int v = scanf("%d %d " INT64, &f, &t, &c);
      assert(v == 3);
      f--; t--;
      input.g[f].push_back(Edge(f, t, c));
      input.g[t].push_back(Edge(t, f, c));
    }
    REP(i, n) {
      int v = scanf(INT64, &input.s[i]);
      assert(v == 1);
    }
    ll ans = Solver::Main(input);
    printf(INT64 "\n", ans);
  }
}
