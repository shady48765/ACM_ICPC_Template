#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>

#define ALL(v) (v).begin(), (v).end()

const int N = 100000;
const int B = 16;

int n, a[N], last[B], left[N], right[N], result[N + 1];
std::vector <int> bits[B];

template <class T>
void update(T &x, T a)
{
	x = std::max(x, a);
}

int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", a + i);
	}
	for (int k = 0; k < B; ++ k) {
		for (int i = n - 1; i >= 0; -- i) {
			if (a[i] >> k & 1) {
				bits[k].push_back(i);
			}
		}
	}
	{
		std::stack <int> stack;
		for (int i = 0; i < n; ++ i) {
			while (!stack.empty() && a[stack.top()] <= a[i]) {
				stack.pop();
			}
			left[i] = stack.empty() ? -1 : stack.top();
			stack.push(i);
		}
	}
	{
		std::stack <int> stack;
		for (int i = n - 1; i >= 0; -- i) {
			while (!stack.empty() && a[stack.top()] <= a[i]) {
				stack.pop();
			}
			right[i] = stack.empty() ? n : stack.top();
			stack.push(i);
		}
	}
	memset(last, -1, sizeof(last));
	memset(result, 0, sizeof(result));
	for (int i = 0; i < n; ++ i) {
		std::vector <std::pair <int, int> > ls, rs;
		for (int k = 0; k < B; ++ k) {
			if (a[i] >> k & 1) {
				last[k] = i;
			}
			if (last[k] > left[i]) {
				ls.push_back(std::make_pair(last[k], k));
			}
			if (!bits[k].empty() && bits[k].back() < i) {
				bits[k].pop_back();
			}
			if (!bits[k].empty() && bits[k].back() < right[i]) {
				rs.push_back(std::make_pair(bits[k].back(), k));
			}
		}
		ls.push_back(std::make_pair(i, -1));
		rs.push_back(std::make_pair(i, -1));
		std::sort(ALL(ls));
		std::sort(ALL(rs));
		for (int p = (int)ls.size() - 1, lo = 0; p >= 0; -- p) {
			if (~ls[p].second) {
				lo |= 1 << ls[p].second;
			}
			for (int q = 0, ro = 0; q < (int)rs.size(); ++ q) {
				if (~rs[q].second) {
					ro |= 1 << rs[q].second;
				}
				int l = rs[q].first - ls[p].first + 1;
				update(result[l], (lo | ro) + a[i]);
			}
		}
	}
	for (int i = 1; i <= n; ++ i) {
		update(result[i], result[i - 1]);
		printf("%d\n", result[i]);
	}
	return 0;
}
