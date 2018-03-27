#include <string.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <cstdio>
#include <ctime>
#include <cmath>

using namespace std;

int main() {
    freopen("jitterbug.in", "rt", stdin);
    freopen("jitterbug.out", "wt", stdout);
    int N;
    cin >> N;
    if (N == 3) {
        cout << "2\n1 2\n2 3\n";
    } else {
        int K = 2 * N / 3;
        cout << K * (K - 1) / 2 + N - K << '\n';
        for (int i = 0; i < K; ++i) {
            for (int j = i + 1; j < K; ++j) {
                cout << i + 1 << ' ' << j + 1 << '\n';
            }
        }
        for (int i = K; i < N; ++i) {
            cout << i << ' ' << i + 1 << '\n';
        }
    }
    return 0;
}
