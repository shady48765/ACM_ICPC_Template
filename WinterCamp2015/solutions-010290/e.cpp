#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>

const int N = 200000;

int n;
int buffer[N << 1], maximum[N + 1];

void update(int k, const int&v)
{
	for (; k <= n; k += ~k & k + 1) {
		maximum[k] = std::max(maximum[k], v);
	}
}

int query(int k)
{
	int ret = -1;
	for (; k >= 0; k -= ~k & k + 1) {
		ret = std::max(ret, maximum[k]);
	}
	return ret;
}

int main()
{
	scanf("%d", &n);
	std::vector <std::pair <std::pair <int, int>, int> > points;
	for (int i = 0; i < n; ++ i) {
		char buf[2];
		int a, b;
		scanf("%s%d%d", buf, &a, &b);
		if (*buf == 'B') {
			a = i - a;
			b = i - b;
		}
		if (0 <= a && a <= i) {
			points.push_back(std::make_pair(std::make_pair(a, i - a), n + n + i));
			points.push_back(std::make_pair(std::make_pair(a + 1, i - a), i));
		}
		if (0 <= b && b <= i) {
			points.push_back(std::make_pair(std::make_pair(b, i - b), n + n + n + i));
			points.push_back(std::make_pair(std::make_pair(b, i - b + 1), n + i));
		}
	}
	std::sort(points.begin(), points.end());
	memset(maximum, -1, sizeof(maximum));
	update(0, 0);
	memset(buffer, -1, sizeof(buffer));
	int result = 0;
	for (int i = 0; i < (int)points.size(); ++ i) {
		int y = points[i].first.second;
		int& ref = buffer[points[i].second % (n + n)];
		if (ref == -1) {
			ref = query(y);
			ref ++;
		} else {
			update(y, ref);
			result = std::max(result, ref);
		}
	}
	printf("%d\n", result);
	return 0;
}
