#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 500;
const int L = 10;
const int MOD = (int)1e9 + 7;

int fact[N + 1], binom[N + 1][N + 1], power[L + 1][N * N + 1], ways[L + 1][N + 1];

void update(int &x, int a)
{
	x += a;
	if (x >= MOD) {
		x -= MOD;
	}
}

int main()
{
	fact[0] = 1;
	for (int i = 1; i <= N; ++ i) {
		fact[i] = (long long)fact[i - 1] * i % MOD;
	}
	memset(binom, 0, sizeof(binom));
	for (int i = 0; i <= N; ++ i) {
		binom[i][0] = 1;
		for (int j = 1; j <= i; ++ j) {
			binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % MOD;
		}
	}
	int n, m, l;
	scanf("%d%d%d", &n, &m, &l);
	for (int i = 0; i <= l; ++ i) {
		power[i][0] = 1;
		for (int j = 1; j <= n * m; ++ j) {
			power[i][j] = (long long)power[i][j - 1] * i % MOD;
		}
	}
	memset(ways, 0, sizeof(ways));
	ways[0][0] = 1;
	int nm = std::min(n, m);
	for (int k = 0; k < l; ++ k) {
		for (int i = 0; i <= nm; ++ i) {
			if (ways[k][i]) {
				for (int j = 0; i + j <= nm; ++ j) {
					int free = n * m - (n - j) * (m - j) - j - 2 * i * j;
					update(ways[k + 1][i + j], (long long)ways[k][i] * binom[n - i][j] % MOD * binom[m - i][j] % MOD * fact[j] % MOD * power[k][free] % MOD);
				}
			}
		}
	}
	int result = 0;
	for (int i = 1; i <= nm; ++ i) {
		int tmp = (long long)ways[l][i] * power[l][(n - i) * (m - i)] % MOD;
		update(result, i & 1 ? tmp : MOD - tmp);
	}
	printf("%d\n", result);
	return 0;
}
