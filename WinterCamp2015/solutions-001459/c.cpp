#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cassert>

using namespace std;

const int MAXN = 100000;
const int MAXK = 100000;

vector<int> a[MAXN];
vector<int> par[MAXN];
int v[MAXK];

int N, K;

void digsort(vector<int> &sub, int x) {
    if (sub.empty()) {
        return;
    }
    if (sub.size() == 1) {
        return;
    }
    if (v[x] == 0) {
        digsort(sub, x + 1);
        return;
    }
    int S = sub.size();
    vector< vector<int> > table(v[x] + 1);
    for (int i = 0; i < S; ++i) {
        table[a[sub[i]][x]].push_back(sub[i]);
    }

    int k = 0;
    for (int i = 0; i <= v[x]; ++i) {
//        cerr << i << ' ' << table[i].size() << '\n';
        digsort(table[i], x + 1);
        for (size_t j = 0; j < table[i].size(); ++j) {
            sub[k] = table[i][j];
            ++k;
        }
    }
}

void rec(vector<int> &sub, vector<int> &perm, int x) {
//    cerr << x << ' ' << sub.size() << '\n';
    if (sub.empty()) {
        return;
    }
    if (sub.size() == 1) {
        perm[0] = sub[0];
        return;
    }
    if (v[x] == 0) {
        rec(sub, perm, x - 1);
        return;
    }
    int S = sub.size();
    vector< vector<int> > table(v[x] + 1);
    for (int i = 0; i < S; ++i) {
        table[a[sub[i]][x]].push_back(sub[i]);
    }
    vector< vector<int> > ptable(v[x] + 1);
    for (int i = 0; i <= v[x]; ++i) {
//        cerr << i << ' ' << table[i].size() << '\n';
        ptable[i].resize(table[i].size());
        rec(table[i], ptable[i], x - 1);
    }
//    cerr << "Rec done\n";
    for (int i = v[x]; i > v[x] / 2; --i) {
        int k = 0;
        for (size_t j = 0; j < table[i].size(); ++j) {
            while (k < table[v[x] - i].size() && par[table[i][j]][x] != par[table[v[x] - i][k]][x]) {
                ++k;
            }
            assert(k < table[v[x] - i].size());
            swap(ptable[i][j], ptable[v[x] - i][k]);
        }
    }
    int k = 0;
    for (int i = 0; i <= v[x]; ++i) {
        for (size_t j = 0; j < table[i].size(); ++j) {
            sub[k] = table[i][j];
            perm[k] = ptable[i][j];
            ++k;
        }
    }
}

int main() {
    freopen("collections.in", "rt", stdin);
    freopen("collections.out", "wt", stdout);

    scanf("%d%d", &N, &K);
    int dump;
    for (int i = 0; i < K; ++i) {
        scanf("%d", &dump);
    }
    for (int i = 0; i < N; ++i) {
        a[i].resize(K);
        for (int j = 0; j < K; ++j) {
            scanf("%d", &a[i][j]);
            v[j] = max(v[j], a[i][j]);
        }
    }
    vector<int> sub(N), perm(N);
    for (int i = 0; i < N; ++i) {
        sub[i] = i;
    }
    digsort(sub, 0);
    for (int i = 0; i < N; ++i) {
        par[i].resize(K);
    }
    for (int i = 0; i < K; ++i) {
        par[sub[0]][i] = sub[0];
    }
    for (int i = 1; i < N; ++i) {
        bool eq = true;
        for (int j = 0; j < K; ++j) {
            if (eq) {
                par[sub[i]][j] = par[sub[i - 1]][j];
            } else {
                par[sub[i]][j] = sub[i];
            }
            if (a[sub[i]][j] != a[sub[i - 1]][j]) {
                eq = false;
            }
        }
    }
    rec(sub, perm, K - 1);
/*    for (int i = 0; i < N; ++i) {
        cerr << perm[i] << ' ';
    }
    cerr << '\n';*/
    vector<int> ans(N);
    for (int i = 0; i < N; ++i) {
        ans[sub[i]] = perm[i];
    }
    for (int i = 0; i < N; ++i) {
        printf("%d %d\n", i + 1, ans[i] + 1);
    }
//    printf("\n");
    return 0;
}
