#include <cstdio>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>

typedef long long Long;

const int N = 200000;

int x[N];

int main()
{
	int n, m, d, d0;
	scanf("%d%d%d%d", &n, &m, &d, &d0);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", x + i);
	}
	if (n == 1) {
		std::cout << x[0] + d0 + (Long)m * d << std::endl;
	} else {
		std::vector <Long> events;
		{
			std::priority_queue <std::pair <Long, int> > queue;
			for (int i = 1; i < n; ++ i) {
				queue.push(std::make_pair(-x[i], -i));
			}
			for (int _ = 0; _ < m; ++ _) {
				std::pair <Long, int> t = queue.top();
				queue.pop();
				events.push_back(-t.first);
				queue.push(std::make_pair(t.first - d, t.second));
			}
		}
		Long result = x[0] + d0;
		for (int i = 1; i <= m; ++ i) {
			result = std::max(result, std::min(events[m - i] - d * (i - 1LL), (Long)x[0] + d0) + (Long)i * d);
		}
		std::cout << result << std::endl;
	}
	return 0;
}
