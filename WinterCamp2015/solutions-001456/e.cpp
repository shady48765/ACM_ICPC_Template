// Grzegorz Guspiel
#include <bits/stdc++.h>
using namespace std;

#define VAR(v) #v << " " << v << " "
#define FOREACH(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)
#define REP(i,n) for(int i=0;i<int(n);++i)
#define REPD(i,n) for (int i = int(n) - 1; i >= 0; i--)
#define SIZE(c) ((int)((c).size()))
#define ALL(v) (v).begin(), (v).end()
#define pb push_back
#define pp pop_back
#define mp make_pair
#define st first
#define nd second

template<typename T> void maxE(T& a, const T& b) { a = max(a, b); }
template<typename T> void minE(T& a, const T& b) { a = min(a, b); }

typedef pair<int, int> PII;

const int MAXN = 1000100;
const int TREE_SPACE = 2097152 + 7;
const int INF = 1000 * 1000 * 1000 + 100;

int n;
int seq[MAXN];

struct SmallTree {
    int s;
    vector<int> t;

    void tupd(int a) {
        while (a) {
            int b = (t[2 * a] < t[2 * a + 1]) ? t[2 * a] : t[2 * a + 1];
            if (t[a] == b) break;
            t[a] = b;
            a /= 2;
        }
    }
    int tget(int a, int b) {
        if (a > b) return INF;
        else if (a == b) return t[a];
        int r = INF;
        if (a % 2) minE(r, t[a++]);
        if (b % 2 == 0) minE(r, t[b--]);
        return min(r, tget(a / 2, b / 2));
    }

    void init(int s_ ) {
        s = 1;
        while (s <= s_) s *= 2;
        t.assign(2 * s, INF);
    }
    void set(int k, int v) {
        t[s + k] = v;
        tupd((s + k) / 2);
    }
    int get(int a, int b) { return tget(s + a, s + b); }
};

struct Range {
    int maxSize;
    vector<PII> points;
    SmallTree tree;

    Range(): maxSize(0) {}
    void init() {
        tree.init(maxSize);
    }
    void addValue(PII point, int value) {
        while (!points.empty() && points.back().nd < point.nd) {
            tree.set(SIZE(points) - 1, INF);
            points.pp();
        }
        assert(points.empty() || points.back().st < point.st);
        points.pb(point);
        assert(SIZE(points) <= maxSize);
        tree.set(SIZE(points) - 1, value);
    }
    PII query(PII state) {
        int x = state.nd;
        int r = state.st;
        int from = lower_bound(ALL(points), mp(x, 0)) - points.begin();
        assert(from == SIZE(points) || points[from].st != x);
        minE(r, tree.get(from, SIZE(points) - 1));
        if (SIZE(points)) maxE(x, points.back().st);
        return mp(r, x);
    }
};

struct BigTree {
    Range t[TREE_SPACE];
    int s;

    PII tget(int a, int b, PII state) {
        assert(a >= 0 && a < TREE_SPACE);
        if (a > b) return state;
        else if (a == b) return t[a].query(state);
        assert(b >= 0 && b < TREE_SPACE);
        if (b % 2 == 0) state = t[b--].query(state);
        int an = a; if (a % 2) an++;
        state = tget(an / 2, b / 2, state);
        assert(a >= 0 && a < TREE_SPACE);
        if (a % 2) state = t[a].query(state);
        return state;
    } 

    void init1(int k) {
        s = 1;
        while (s <= k) s *= 2;
        REP (i, 2 * s) {
            assert(i >= 0 && i < TREE_SPACE);
            t[i] = Range();
        }
    }
    void allocateElement(int a) {
        assert(a >= 0 && a < s);
        a += s;
        while (a) {
            assert(a >= 0 && a < TREE_SPACE);
            t[a].maxSize++;
            a /= 2;
        }
    }
    void init2() {
        REP (i, 2 * s) {
            assert(i >= 0 && i < TREE_SPACE);
            t[i].init();
        }
    }
    void clear() {
        REP (i, 2 * s) t[i] = Range();
    }
    void addValue(PII point, int value) {
        int a = point.nd + s;
        assert(a >= s && a < 2 * s);
        while (a) {
            assert(a >= 0 && a < TREE_SPACE);
            t[a].addValue(point, value);
            a /= 2;
        }
    }
    int queryTo(int y) { 
        assert(y >= 0 && y < s);
        int r = tget(s, s + y, mp(INF, -1)).st;
        return r;
    }
};
BigTree bigTree;

int main() {
	int z; cin >> z;
	while(z--) {
        vector<PII> tmpSeq;
        vector<PII> vals;
        assert(scanf("%d", &n) == 1);
        REP (i, n) {
            int a; assert(scanf("%d", &a) == 1);
            tmpSeq.pb(mp(a, i));
            vals.pb(mp(a, i));
        }
        sort(ALL(vals));
        vals.resize(unique(ALL(vals)) - vals.begin());
        REP (i, n) {
            seq[i] = lower_bound(ALL(vals), tmpSeq[i]) - vals.begin();
        }

        bigTree.init1(SIZE(vals));
        REP (i, n) bigTree.allocateElement(seq[i]);
        bigTree.init2();

        REP (i, n) {
            int len = bigTree.queryTo(seq[i]) + 1;
            if (len >= INF) len = 1;
            bigTree.addValue(mp(i, seq[i]), len);
        }

        cout << bigTree.queryTo(SIZE(vals) - 1) << endl;

        bigTree.clear();
	}
	return 0;
}