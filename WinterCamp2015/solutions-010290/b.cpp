#include <cstdio>
#include <cstring>
#include <vector>

const int N = 200000;
const int D = 4;

char buf[N + 1];
std::vector <bool> win[N + 1];

int main()
{
	int n, m, q;
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 0; i <= n; ++ i) {
		win[i].resize(i < D ? m + 1 : D);
	}
	scanf("%s", buf);
	for (int i = 1; i <= n; ++ i) {
		win[i][0] = buf[i - 1] == '1';
	}
	scanf("%s", buf);
	for (int i = 1; i <= m; ++ i) {
		win[0][i] = buf[i - 1] == '1';
	}
	for (int i = 1; i <= n; ++ i) {
		for (int j = 1; j < (int)win[i].size(); ++ j) {
			win[i][j] = !win[i - 1][j] || !win[i][j - 1];
		}
	}
	while (q --) {
		int x, y;
		scanf("%d%d", &x, &y);
		bool valid = true;
		if (y < (int)win[x].size()) {
			valid = win[x][y];
		} else if (x >= y) {
			valid = win[x - y + D - 1][D - 1];
		} else {
			valid = win[D - 1][y - x + D - 1];
		}
		puts(valid ? "Yes" : "No");
	}
	return 0;
}
