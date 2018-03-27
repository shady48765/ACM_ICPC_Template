#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <utility>
#include <vector>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

typedef std::pair <int, int> Pair;

const int N = 1000;

int n, m;
char map[N][N + 1];
int cost[N][N + 1];
std::vector <Pair > adj[N * 2 + 1][N * 2 + 1];

int vis[N * 2 + 1][N * 2 + 1];

void add_edge(int x0, int y0, int x1, int y1)
{
	adj[x0][y0].push_back(Pair(x1, y1));
	adj[x1][y1].push_back(Pair(x0, y0));
}

void dfs(int tag, int x, int y)
{
	if (vis[x][y] == -1) {
		vis[x][y] = tag;
		foreach (it, adj[x][y]) {
			dfs(tag, it->first, it->second);
		}
	}
}

int find(std::vector <int> &p, int u)
{
	if (p[u] == -1) {
		return u;
	}
	return p[u] = find(p, p[u]);
}

void merge(std::vector <int> &p, int a, int b)
{
	if (find(p, a) != find(p, b)) {
		p[find(p, a)] = find(p, b);
	}
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) {
		scanf("%s", map[i]);
		for (int j = 0; j < m; ++ j) {
			int x = 2 * i + 1;
			int y = 2 * j + 1;
			if (map[i][j] == '/') {
				add_edge(x - 1, y, x, y - 1);
				add_edge(x + 1, y, x, y + 1);
			} else {
				add_edge(x - 1, y, x, y + 1);
				add_edge(x + 1, y, x, y - 1);
			}
		}
	}
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < m; ++ j) {
			scanf("%d", cost[i] + j);
		}
	}
	memset(vis, -1, sizeof(vis));
	int comp = 1;
	for (int i = 0; i <= 2 * n; ++ i) {
		for (int j = 0; j <= 2 * m; ++ j) {
			if ((i + j & 1) && vis[i][j] == -1) {
				dfs(comp ++, i, j);
			}
		}
	}
	std::vector <std::pair <int, Pair> > edges;
	for (int i = 0; i < n; ++ i) {
		for (int j = 0; j < m; ++ j) {
			int x = 2 * i + 1;
			int y = 2 * j + 1;
			int u = vis[x - 1][y];
			int v = vis[x][y + 1];
			if (map[i][j] == '\\') {
				v = vis[x][y - 1];
			}
			if (u != v) {
				edges.push_back(std::make_pair(cost[i][j], Pair(u, v)));
			}
		}
	}
	std::vector <int> pat(comp, -1);
	for (int i = 0; i <= 2 * n; ++ i) {
		for (int j = 0; j <= 2 * m; ++ j) {
			if ((i + j & 1) && (i == 0 || j == 0 || i == 2 * n || j == 2 * m)) {
				merge(pat, vis[i][j], 0);
			}
		}
	}
	std::sort(edges.begin(), edges.end());
	int result = 0;
	foreach (it, edges) {
		int x = it->second.first;
		int y = it->second.second;
		if (find(pat, x) != find(pat, y)) {
			result += it->first;
			pat[find(pat, x)] = find(pat, y);
		}
	}
	printf("%d\n", result);
	return 0;
}
