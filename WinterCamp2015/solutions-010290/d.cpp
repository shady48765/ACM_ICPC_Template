#include <cassert>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <set>

#define foreach(i, v) for (__typeof((v).begin()) i = (v).begin(); i != (v).end(); ++ i)

const int N = 200000;
const int MOD = (int)1e9 + 7;

int nxt[N], pat[N], dep[N];
std::vector <int> children[N];

void dfs(int p, int u)
{
	dep[u] = ~p ? dep[p] + 1 : 0;
	foreach (it, children[u]) {
		dfs(u, *it);
	}
}

int find(int u)
{
	if (pat[u] == -1) {
		return u;
	}
	return pat[u] = find(pat[u]);
}

std::set <int> graph[N];

void add_edge(int a, int b)
{
	graph[a].insert(b);
	graph[b].insert(a);
}

bool removed[N];

int main()
{
	int n, c;
	scanf("%d%d", &n, &c);
	nxt[0] = -1;
	for (int i = 1; i < n; ++ i) {
		scanf("%d", nxt + i);
		nxt[i] --;
	}
	for (int i = 1; i < n; ++ i) {
		int p = nxt[i - 1] + 1;
		if (p >= i) {
			return 0;
		}
		children[p].push_back(i);
	}
	memcpy(pat, nxt, sizeof(nxt));
	for (int i = 1; i < n; ++ i) {
		int j = i - 1;
		while (j >= 0) {
			j = nxt[j];
			if (j + 1 == nxt[i]) {
				break;
			}
			add_edge(find(j + 1), find(i));
		}
	}
	memset(dep, -1, sizeof(dep));
	for (int i = 0; i < n; ++ i) {
		if (dep[i] == -1) {
			dfs(-1, i);
		}
	}
	std::vector <std::pair <int, int> > order;
	for (int i = 0; i < n; ++ i) {
		if (find(i) == i) {
			order.push_back(std::make_pair(dep[i], i));
		}
	}
	std::sort(order.begin(), order.end());
	memset(removed, 0, sizeof(removed));
	int result = 1;
	for (int i = (int)order.size() - 1; i >= 0; -- i) {
		int u = order[i].second;
		int cc = c;
		foreach (it, graph[u]) {
			int v = *it;
			if (!removed[v]) {
				cc --;
			}
		}
		result = (long long)result * std::max(cc, 0) % MOD;
		removed[u] = true;
	}
	printf("%d\n", result);
	std::vector <int> degs;
	for (int i = 0; i < n; ++ i) {
		if (find(i) == i) {
			degs.push_back(graph[i].size());
		}
	}
	//std::sort(degs.begin(), degs.end(), std::greater <int>());
	//for (int i = 0; i < 10 && i < (int)degs.size(); ++ i) {
	//	fprintf(stderr, "%d, ", degs[i]);
	//}
	//fprintf(stderr, "\n");
	return 0;
}
