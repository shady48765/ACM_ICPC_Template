#include <cstdio>
#include <cstring>
#include <algorithm>

const int N = 100000;
const int Q = 10000;
const int MOD = (int)1e9 + 7;

int n[Q], m[Q], a[Q], order[Q], res[Q];

bool by_a(int i, int j)
{
	return a[i] < a[j];
}

int mu[N + 1], cnt[N + 1];

void add(int k, int v)
{
	for (; k; k -= k & -k) {
		cnt[k] += v;
		if (cnt[k] >= MOD) {
			cnt[k] -= MOD;
		}
	}
}

int query(int k)
{
	int ret = 0;
	for (; k <= N; k += k & -k) {
		ret += cnt[k];
		if (ret >= MOD) {
			ret -= MOD;
		}
	}
	return ret;
}

inline int sum(int n)
{
	return (long long)n * (n + 1) / 2 % MOD;
}

int solve(int n, int m)
{
	int ret = 0;
	int d = 1;
	while (d <= n && d <= m) {
		int dd = std::min(n / (n / d), m / (m / d)) + 1;
		ret += (long long)sum(n / d) * sum(m / d) % MOD * (query(d) + MOD - query(dd)) % MOD;
		if (ret >= MOD) {
			ret -= MOD;
		}
		d = dd;
	}
	return ret;
}

int main()
{
	memset(mu, 0, sizeof(mu));
	mu[1] = 1;
	for (int i = 1; i <= N; ++ i) {
		for (int j = i + i; j <= N; j += i) {
			mu[j] += MOD - mu[i];
			if (mu[j] >= MOD) {
				mu[j] -= MOD;
			}
		}
	}
	int q;
	scanf("%d", &q);
	for (int i = 0; i < q; ++ i) {
		scanf("%d%d%d", n + i, m + i, a + i);
		order[i] = i;
	}
	std::sort(order, order + q, by_a);
	memset(cnt, 0, sizeof(cnt));
	for (int d = 1, i = 0; d <= N; ++ d) {
		for (int k = 1; k * d <= N; ++ k) {
			add(k * d, (long long)d * mu[k] % MOD * k % MOD * k % MOD);
		}
		while (i < q && a[order[i]] == d) {
			res[order[i]] = solve(n[order[i]], m[order[i]]);
			i ++;
		}
	}
	for (int i = 0; i < q; ++ i) {
		printf("%d\n", res[i]);
	}
	return 0;
}
