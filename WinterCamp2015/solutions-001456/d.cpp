#include <bits/stdc++.h>
using namespace std;

#define VAR(v) #v << " " << v << " "
#define REP(i,n) for(int i=0;i<int(n);++i)
#define SIZE(c) ((int)((c).size()))
#define ALL(v) (v).begin(), (v).end()
#define pb push_back
#define mp make_pair
#define st first
#define nd second

template<typename T> void maxE(T& a, const T& b) { a = max(a, b); }

const int MAXN = 2010;
int n;
int d[MAXN];
int nx[MAXN][MAXN];
int t[MAXN][MAXN];

int main() {
	int z; assert(scanf("%d", &z) == 1);
	while(z--) {
        assert(scanf("%d", &n) == 1);
        REP (i, n) assert(scanf("%d", d + i) == 1);
        REP (j, n) {
            int k = j + 1;
            for (int i = j - 1; i >= 0; i--) {
                while (k < n && d[k] - d[j] < d[j] - d[i]) k++;
                if (d[k] - d[j] == d[j] - d[i]) {
                    nx[i][j] = k;
                } else nx[i][j] = n;
            }
        }
        int best = 0;
        for (int i = n - 1; i >= 0; i--) for (int j = i + 1; j < n; j++) {
            t[i][j] = 0;
            if (nx[i][j] == n) continue;
            maxE(t[i][j], 1 + t[j][nx[i][j]]);
            maxE(best, t[i][j]);
        }
        printf("%d\n", best + 2);
	}
	return 0;
}