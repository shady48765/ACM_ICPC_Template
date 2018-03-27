#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 40;
const int MOD = (int)1e9 + 7;

int mat[4][N][N];

int inv(int a)
{
	assert(a != 0);
	return a == 1 ? 1 : (long long)(MOD - MOD / a) * inv(MOD % a) % MOD;
}

int det(int mat[N][N], int n)
{
	int ret = 1;
	for (int j = 0; j < n; ++ j) {
		int p = j;
		while (p < n && !mat[p][j]) {
			p ++;
		}
		if (p == n) {
			return 0;
		}
		if (p != j) {
			ret = (long long)ret * (MOD - 1) % MOD;
			for (int k = 0; k < n; ++ k) {
				std::swap(mat[p][k], mat[j][k]);
			}
		}
		for (int i = j + 1; i < n; ++ i) {
			if (mat[i][j]) {
				int coef = (long long)mat[i][j] * inv(mat[j][j]) % MOD;
				for (int k = j; k < n; ++ k) {
					mat[i][k] += MOD - (long long)coef * mat[j][k] % MOD;
					if (mat[i][k] >= MOD) {
						mat[i][k] -= MOD;
					}
				}
			}
		}
		ret = (long long)ret * mat[j][j] % MOD;
	}
	return ret;
}

int xcoef[N], ycoef[N];

int main()
{
	int n, m, p, q;
	scanf("%d%d%d%d", &n, &m, &p, &q);
	memset(mat, 0, sizeof(mat));
	for (int i = 0; i < m; ++ i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a --;
		b --;
		c --;
		mat[c][a][b] --;
		mat[c][b][a] --;
		mat[c][a][a] ++;
		mat[c][b][b] ++;
	}
	for (int k = 0; k < 3; ++ k) {
		for (int i = 0; i < n; ++ i) {
			for (int j = 0; j < n; ++ j) {
				if (mat[k][i][j] < 0) {
					mat[k][i][j] += MOD;
				}
			}
		}
	}
	int answer = 0;
	for (int x = 0; x < n; ++ x) {
		for (int y = 0; y < n; ++ y) {
			for (int i = 0; i < n; ++ i) {
				for (int j = 0; j < n; ++ j) {
					int value[3] = {1, x, y};
					int &ref = mat[3][i][j] = 0;
					for (int k = 0; k < 3; ++ k) {
						ref += (long long)value[k] * mat[k][i][j] % MOD;
						if (ref >= MOD) {
							ref -= MOD;
						}
					}
				}
			}
			int res = det(mat[3], n - 1);
			memset(xcoef, 0, sizeof(xcoef));
			xcoef[0] = 1;
			for (int i = 0; i < n; ++ i) {
				if (i != x) {
					for (int k = n - 2; k >= 0; -- k) {
						xcoef[k + 1] += xcoef[k];
						if (xcoef[k + 1] >= MOD) {
							xcoef[k + 1] -= MOD;
						}
						xcoef[k] = (long long)xcoef[k] * (MOD - i) % MOD;
					}
					res = (long long)res * inv((x + MOD - i) % MOD) % MOD;
				}
			}
			memset(ycoef, 0, sizeof(ycoef));
			ycoef[0] = 1;
			for (int j = 0; j < n; ++ j) {
				if (j != y) {
					for (int k = n - 2; k >= 0; -- k) {
						ycoef[k + 1] += ycoef[k];
						if (ycoef[k + 1] >= MOD) {
							ycoef[k + 1] -= MOD;
						}
						ycoef[k] = (long long)ycoef[k] * (MOD - j) % MOD;
					}
					res = (long long)res * inv((y + MOD - j) % MOD) % MOD;
				}
			}
			for (int i = 0; i <= p; ++ i) {
				for (int j = 0; j <= q; ++ j) {
					int cnt = (long long)res * xcoef[i] % MOD * ycoef[j] % MOD;
					answer += cnt;
					if (answer >= MOD) {
						answer -= MOD;
					}
				}
			}
		}
	}
	printf("%d\n", answer);
	return 0;
}
