#include <cstdio>
#include <cstring>
#include <queue>

const int N = 40;
const int MOD = (int)1e9 + 7;

bool graph[N][N];
int color[N], coef[N][N][2][2], value[N];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	memset(coef, 0, sizeof(coef));
	for (int i = 0; i < m; ++ i) {
		int u, v;
		scanf("%d%d", &u, &v);
		u --;
		v --;
		graph[u][v] = graph[v][u] = true;
		for (int i = 0; i < 2; ++ i) {
			for (int j = 0; j < 2; ++ j) {
				scanf("%d", &coef[u][v][i][j]);
				coef[v][u][j][i] = coef[u][v][i][j];
			}
		}
	}
	std::vector <int> small;
	memset(color, -1, sizeof(color));
	for (int i = 0; i < n; ++ i) {
		if (color[i] == -1) {
			std::vector <int> vertices[2];
			color[i] = 0;
			std::queue <int> queue;
			queue.push(i);
			while (!queue.empty()) {
				int u = queue.front();
				vertices[color[u]].push_back(u);
				queue.pop();
				for (int v = 0; v < n; ++ v) {
					if (graph[u][v] && color[v] == -1) {
						color[v] = color[u] ^ 1;
						queue.push(v);
					}
				}
			}
			std::vector <int> &v = vertices[0].size() < vertices[1].size() ? vertices[0] : vertices[1];
			small.insert(small.end(), v.begin(), v.end());
		}
	}
	int result = 0;
	for (int mask = 0; mask < 1 << (int)small.size(); ++ mask) {
		memset(value, -1, sizeof(value));
		for (int i = 0; i < (int)small.size(); ++ i) {
			value[small[i]] = mask >> i & 1;
		}
		int product = 1;
		for (int i = 0; i < n; ++ i) {
			if (value[i] == -1) {
				int sum[2];
				sum[0] = sum[1] = 1;
				for (int j = 0; j < (int)small.size(); ++ j) {
					int v = small[j];
					if (graph[i][v]) {
						sum[0] = (long long)sum[0] * coef[i][v][0][value[v]] % MOD;
						sum[1] = (long long)sum[1] * coef[i][v][1][value[v]] % MOD;
					}
				}
				product = (long long)product * (sum[0] + sum[1]) % MOD;
			}
		}
		result += product;
		if (result >= MOD) {
			result -= MOD;
		}
	}
	printf("%d\n", result);
	return 0;
}
