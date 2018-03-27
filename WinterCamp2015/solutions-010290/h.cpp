#include <stdlib.h>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 1000;

int head[N], to[N << 1], length[N << 1], next[N << 1], dist[N][N];

int cal(int n) {
	if (n <= 2) {
		return 0;
	}
	return 1 + cal(2 * (n - 1) / 3 + 1);
}

void add_edge(int u, int v, int w)
{
	static int count = 0;
	to[count] = v;
	length[count] = w;
	next[count] = head[u];
	head[u] = count ++;
}

void traverse(int* dist, int p, int u)
{
	for (int it = head[u]; ~it; it = next[it]) {
		int v = to[it];
		if (v != p) {
			dist[v] = dist[u] + length[it];
			traverse(dist, u, v);
		}
	}
}

std::vector <int> position[N];
bool active[N];
int size[N], bias[N];

void prepare(int p, int u)
{
	size[u] = 1;
	bias[u] = 0;
	for (int it = head[u]; ~it; it = next[it]) {
		int v = to[it];
		if (v != p && active[v]) {
			prepare(u, v);
			size[u] += size[v];
			bias[u] = std::max(bias[u], size[v]);
		}
	}
}

void search(int p, int u, std::vector <int> &nodes)
{
	nodes.push_back(u);
	for (int it = head[u]; ~it; it = next[it]) {
		int v = to[it];
		if (v != p && active[v]) {
			search(u, v, nodes);
		}
	}
}

void solve(int d, const std::vector <int> &all)
{
	if (d >= 0) {
		if ((int)all.size() == 1) {
			solve(d - 1, all);
			return;
		}
		memset(active, 0, sizeof(active));
		foreach (it, all) {
			active[*it] = true;
		}
		int o = all[0];
		prepare(-1, o);
		int r = o;
		foreach (it, all) {
			int v = *it;
			bias[v] = std::max(bias[v], size[o] - size[v]);
			if (bias[v] < bias[r]) {
				r = v;
			}
		}
//printf("root %d\n", r + 1);
		std::vector <std::pair <int, int> > children;
		for (int it = head[r]; ~it; it = next[it]) {
			int v = to[it];
			if (active[v]) {
				int s = size[v];
				if (s > size[r]) {
					s = size[o] - size[r];
				}
				children.push_back(std::make_pair(s, v));
			}
		}
		std::sort(children.begin(), children.end());
		std::reverse(children.begin(), children.end());
		int budget = 2 * (size[o] - 1) / 3;
		int t = 0;
		while (children[t].first <= budget) {
			budget -= children[t ++].first;
		}
		std::vector <int> pnodes, nnodes;
		pnodes.push_back(r);
		for (int i = 0; i < t; ++ i) {
			search(r, children[i].second, pnodes);
		}
		foreach (it, pnodes) {
			int v = *it;
			position[v][d] = dist[r][v];
		}
		nnodes.push_back(r);
		for (int i = t; i < (int)children.size(); ++ i) {
			search(r, children[i].second, nnodes);
		}
		foreach (it, nnodes) {
			int v = *it;
			position[v][d] = -dist[r][v];
		}
//for (int v : pnodes) printf("(%d, %d), ", v + 1, position[v][d]); puts("");
//for (int v : nnodes) printf("(%d, %d), ", v + 1, position[v][d]); puts("");
		solve(d - 1, pnodes);
		std::vector <int> tmp(position[r]);
		solve(d - 1, nnodes);
		for (int j = 0; j < d; ++ j) {
			int offset = tmp[j] - position[r][j];
			foreach (it, nnodes) {
				int v = *it;
				position[v][j] += offset;
			}
		}
	}
}

int main()
{
	int n;
	scanf("%d", &n);
	memset(head, -1, sizeof(head));
	for (int i = 0; i < n - 1; ++ i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		a --;
		b --;
		add_edge(a, b, c);
		add_edge(b, a, c);
	}
	memset(dist, 0, sizeof(dist));
	for (int i = 0; i < n; ++ i) {
		traverse(dist[i], -1, i);
	}
	int m = std::max(cal(n), 1);
	for (int i = 0; i < n; ++ i) {
		position[i].resize(m);
	}
	std::vector <int> all;
	for (int i = 0; i < n; ++ i) {
		all.push_back(i);
	}
	solve(m - 1, all);
	printf("%d\n", m);
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < m; ++ j) {
			printf("%d%c", position[i][j], " \n"[j == m - 1]);
		}
	}
	return 0;
}
