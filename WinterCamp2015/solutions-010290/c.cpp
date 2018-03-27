#include <cstdio>
#include <cstring>
#include <vector>

const int N = 1000000;

int n, div[N + 1], nonsqr[N + 1], sqrt[N + 1];
bool vis[N + 1];
std::vector <int> nums[N + 1];

int main()
{
	memset(div, 0, sizeof(div));
	for (int p = 2; p * p <= N; ++ p) {
		if (!div[p]) {
			div[p] = p;
			for (int i = p * p; i <= N; i += p) {
				div[i] = p;
			}
		}
	}
	for (int i = 1; i * i <= N; ++ i) {
		sqrt[i * i] = i;
	}
	nonsqr[1] = 1;
	for (int i = 2; i <= N; ++ i) {
		int &d = div[i];
		if (!d) {
			d = i;
		}
		if ((i / d) % d == 0) {
			nonsqr[i] = nonsqr[i / d / d];
		} else {
			nonsqr[i] = nonsqr[i / d] * d;
		}
	}
	scanf("%d", &n);
	for (int i = 0; i < n; ++ i) {
		int x;
		scanf("%d", &x);
		vis[x] = true;
		nums[nonsqr[x]].push_back(sqrt[x / nonsqr[x]]);
	}
	int result = 0;
	for (int d = 1; d <= N; ++ d) {
		std::vector <int> &vs = nums[d];
		int n = vs.size();
		for (int i = 0; i < n; ++ i) {
			for (int j = i + 1; j < n; ++ j) {
				long long product = d * vs[i] * vs[j];
				result += product <= N && vis[product];
			}
		}
	}
	printf("%d\n", result);
	return 0;
}
