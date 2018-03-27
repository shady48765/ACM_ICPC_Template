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
// Problem: IPCPC Teams
// Solution by: MORI Shingo
// O(nlogn)
//
// implement 31min
// debug 42min
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
const int INF = 2e+9 + 3;

#define REP(i, n) for (int i = 0; i < (int)(n); i++)
#define FOR(i, s, n) for (int i = (s); i < (int)(n); i++)
#define FOREQ(i, s, n) for (int i = (s); i <= (int)(n); i++)
#define FORIT(it, c) for (__typeof((c).begin())it = (c).begin(); it != (c).end(); it++)
#define MEMSET(v, h) memset((v), h, sizeof(v))

//a x + b y = gcd(a, b)
long long extgcd(long long a, long long b, long long &x, long long &y) {
  long long g = a; x = 1; y = 0;
  if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
  return g;
}

long long InvMod(long long a, long long mod) {
  long long x, y;
  if (extgcd(a, mod, x, y) == 1) { return (x + mod) % mod; }
  return 0;
}

long long powmod(long long base, long long power, int mod) {
  long long ans = 1;
  while (power > 0) {
    if (power & 1) { ans = ans * base % mod; }
    power >>= 1;
    base = base * base % mod;
  }
  return ans;
}

struct UnionFind {
  int parent[40];
  UnionFind() { memset(parent, -1, sizeof(parent)); }
  bool unionSet(int x, int y) {
    x = root(x); y = root(y);
    if (x == y) { return false; }
    if (parent[y] < parent[x]) { swap(x, y); }
    parent[x] += parent[y];
    parent[y] = x;
    return true;
  }
  bool findSet(int x, int y) {
    return root(x) == root(y);
  }
  int root(int x) { return parent[x] < 0 ? x : parent[x] = root(parent[x]); }
};

ll n;
int m;
int cnt;
int as[100];
int bs[100];
ll fact[4000000];
const ll MOD = 1e+9 + 9;

ll CalcSet(ll c1, ll c2) {
  ll c0 = c1 - c2;
  ll ret = fact[c1];
  ret = (ret * InvMod(fact[c0 / 3], MOD)) % MOD;
  ret = (ret * InvMod(powmod(6, c0 / 3, MOD), MOD)) % MOD;
  return ret;

}

ll visit[1 << 18];
ll Calc(int distinct) {
  if (visit[distinct]) { return 0; }
  visit[distinct] = true;
  UnionFind ufind;
  REP(i, m) {
    if ((distinct >> i) & 1) { continue; }
    ufind.unionSet(as[i], bs[i]);
  }
  ll c2 = 0;
  ll c3 = 0;
  REP(i, cnt) {
    int s = -ufind.parent[i];
    if (s <= 1) { continue; }
    if (s == 2) { c2++; }
    if (s == 3) { c3++; }
    if (s >= 4) { return 0; }
  }
  ll c1 = n - c2 * 2 - c3 * 3;
  if (c1 - c2 < 0) { return 0; }
  ll ret = CalcSet(c1, c2);
  REP(i, m) {
    if (!((distinct >> i) & 1)) { continue; }
    int ndistinct = distinct & (~(1 << i));
    ret = (ret - Calc(ndistinct) + MOD) % MOD;
  }
  return ret % MOD;
}

int main() {
  while (scanf(INT64 " %d", &n, &m) > 0) {
    MEMSET(visit, false);
    n *= 3;
    fact[0] = 1;
    REP(i, n + 10) {
      fact[i + 1] = (i + 1) * fact[i] % MOD;
    }
    int distinct = 0;
    map<int, int> mapto;
    cnt = 0;
    REP(i, m) {
      int c;
      int v = scanf("%d %d %d", &as[i], &bs[i], &c);
      assert(v == 3);
      as[i]--; bs[i]--;
      if (!mapto.count(as[i])) { mapto[as[i]] = cnt++; }
      if (!mapto.count(bs[i])) { mapto[bs[i]] = cnt++; }
      as[i] = mapto[as[i]]; bs[i] = mapto[bs[i]];
      distinct |= c << i;
    }
    UnionFind ufind;
    ll ans = Calc(distinct);
    REP(i, m) {
      if ((distinct >> i) & 1) { continue; }
      ufind.unionSet(as[i], bs[i]);
    }
    REP(i, m) {
      if ((distinct >> i) & 1) {
        if (ufind.findSet(as[i], bs[i])) { ans = 0; }
      }
    }
    printf(INT64 "\n", ans);
  }
}
