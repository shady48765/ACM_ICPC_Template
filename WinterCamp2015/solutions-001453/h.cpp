#include <cassert>
#include <cstdio>
#include <utility>
#include <vector>

int order(int a, int p)
{
	int o = 1;
	int tmp = a % p;
	while (tmp != 1) {
		o ++;
		tmp = (long long)tmp * a % p;
	}
	return o;
}

typedef std::pair <int, std::vector <int> > Result;

int size(const Result &r)
{
	return r.second.size();
}

int get(const Result &r, int i)
{
	return i < (int)r.second.size() ? r.second[i] : 0;
}

int pow(int a, int n, int p)
{
	int ret = 1;
	while (n) {
		if (n & 1) {
			ret = (long long)ret * a % p;
		}
		a = (long long)a * a % p;
		n >>= 1;
	}
	return ret;
}

int inverse(int a, int p)
{
	assert(a > 0);
	return pow(a, p - 2, p);
}

Result count(const std::vector <int> &fact, const std::vector <int> &prod, int n, int p)
{
	int a = prod.size();
	int ret = (long long)pow(prod[a - 1], n / a, p) * prod[n % a] % p;
	n /= a;
	std::vector <int> count;
	count.push_back(n);
	while (n) {
		ret = (long long)ret * pow(fact[p - 1], n / p, p) % p * fact[n % p] % p;
		count.push_back(n /= p);
	}
	return std::make_pair(ret, count);
}

//void dump(const Result &r)
//{
//	printf("%d, {", r.first);
//	for (int v : r.second) {
//		printf("%d, ", v);
//	}
//	puts("}");
//}

int solve(int q, int n, int k, int p)
{
	if (q == p) {
		return 1;
	}
	int a = order(q, p);
	std::vector <int> fact(p);
	fact[0] = 1;
	for (int i = 1; i < p; ++ i) {
		fact[i] = (long long)fact[i - 1] * i % p;
	}
	std::vector <int> prod(a);
	prod[0] = 1;
	for (int i = 1; i < a; ++ i) {
		prod[i] = (long long)prod[i - 1] * q % p;
	}
	for (int i = 1; i < a; ++ i) {
		prod[i] = (long long)prod[i - 1] * (prod[i] + p - 1) % p;
	}
	Result x = count(fact, prod, n, p);
//dump(x);
	Result y = count(fact, prod, k, p);
//dump(y);
	Result z = count(fact, prod, n - k, p);
//dump(z);
	int m = std::max(size(x), std::max(size(y), size(z)));
	int result = (long long)x.first * inverse(y.first, p) % p * inverse(z.first, p) % p;
	for (int i = 0; i < m; ++ i) {
		int d = get(x, i) - get(y, i) - get(z, i);
		assert(d >= 0);
		if (d) {
			result = 0;
		}
	}
	return result;
}

int main()
{
	int q, n, k, p;
	scanf("%d%d%d%d", &q, &n, &k, &p);
	printf("%d\n", solve(q, n, k, p));
	return 0;
}
