#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#include <algorithm>

const int MOD = (int)1e9 + 7;

struct Point
{
	Point() : x(0), y(0) {}
	Point(int x, int y) : x(x), y(y) {}

	Point& operator -= (const Point &rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		return *this;
	}

	int quadrant() const
	{
		if (y != 0) {
			return y > 0;
		}
		return x > 0;
	}

	long long norm() const
	{
		return (long long)x * x + (long long)y * y;
	}

	int x, y;
};

bool operator == (const Point &a, const Point &b)
{
	return a.x == b.x && a.y == b.y;
}

const Point operator - (Point a, const Point &b)
{
	return a -= b;
}

long long det(const Point &a, const Point &b)
{
	return (long long)a.x * b.y - (long long)a.y * b.x;
}

long long dot(const Point &a, const Point &b)
{
	return (long long)a.x * b.x + (long long)a.y * b.y;
}

bool operator < (const Point &a, const Point &b)
{
	if (a.quadrant() != b.quadrant()) {
		return a.quadrant() < b.quadrant();
	}
	long long d = det(a, b);
	if (d != 0) {
		return d > 0;
	}
	return a.norm() < b.norm();
}

const int N = 2000;

unsigned int two[N + 1];
Point p[N];

bool check(const std::pair <Point, int> &a, const std::pair <Point, int> &b)
{
	long long d = det(a.first, b.first);
	if (d != 0) {
		return d > 0;
	}
	if (dot(a.first, b.first) < 0) {
		return true;
	}
	d = a.first.norm() - b.first.norm();
	if (d != 0) {
		return d < 0;
	}
	return a.second < b.second;
}

int main()
{
	int n;
	scanf("%d", &n);
	two[0] = 1;
	for (int i = 1; i <= n; ++ i) {
		two[i] = (two[i - 1] << 1) % MOD;
	}
	for (int i = 0; i < n; ++ i) {
		scanf("%d%d", &p[i].x, &p[i].y);
	}
	unsigned int result = 0;
	for (int i = 0; i < n; ++ i) {
		std::vector <std::pair <Point, int> > order;
		int coincide = 0;
		for (int j = 0; j < n; ++ j) {
			if (p[i] == p[j]) {
				coincide += j < i;
			} else {
				order.push_back(std::make_pair(p[j] - p[i], j));
			}
		}
//printf("#%d (%d, %d)\n", i, p[i].x, p[i].y);
		std::sort(order.begin(), order.end());
		int m = order.size();
		for (int j = 0, s = 1; j < m; ++ j) {
			while (s < m && check(order[j], order[(j + s) % m])) {
				s ++;
			}
//printf("-> (%d, %d) %d %d\n", p[order[j].second].x, p[order[j].second].y, coincide + m - s, s);
			result += two[coincide + m - s];
			if (result >= MOD) {
				result %= MOD;
			}
			if (s > 1) {
				s --;
			}
		}
	}
	std::sort(p, p + n);
	for (int i = 0; i < n; ) {
		int j = i;
		while (j < n && p[i] == p[j]) {
			j ++;
		}
		result += two[j - i] - 1;
		if (result >= MOD) {
			result %= MOD;
		}
		i = j;
	}
	printf("%d\n", result%MOD);
	return 0;
}
