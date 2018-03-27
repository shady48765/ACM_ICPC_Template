#include <cstdio>
#include <algorithm>
#include <iostream>
#include <queue>

const int N = 200000;

int n, a[N], cur[N + 1];
long long sum[N + 1];

inline void add(std::priority_queue <std::pair <long long, int> > &heap, int i)
{
	if (cur[i] < n) {
		heap.push(std::make_pair(-(sum[i] + a[cur[i]]), i));
	}
}

int main()
{
	int k;
	scanf("%d%d", &n, &k);
	sum[0] = 0;
	for (int i = 0; i < n; ++ i) {
		scanf("%d", a + i);
		if (a[i] < 0) {
			sum[0] += a[i];
			a[i] *= -1;
		}
	}
	k ++;
	std::sort(a, a + n);
	int m = 1;
	cur[0] = 0;
	std::priority_queue <std::pair <long long, int> > heap;
	heap.push(std::make_pair(-(sum[0] + a[0]), 0));
	while (m < k) {
		int p = heap.top().second;
		heap.pop();
		sum[m] = sum[p] + a[cur[p]];
		cur[p] ++;
		cur[m] = cur[p];
		add(heap, m);
		m ++;
		add(heap, p);
	}
	std::ios::sync_with_stdio(false);
	bool first = true;
	m = 1;
	for (int i = 0; m < k; ++ i) {
		if (sum[i] == 0 && first) {
			first = false;
			continue;
		}
		m ++;
		std::cout << sum[i] << std::endl;
	}
	return 0;
}
