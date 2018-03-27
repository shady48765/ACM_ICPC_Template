#include <cstdio>
#include <cstring>

const int N = 5000;

int n;
long long a[N];

int main()
{
	scanf("%d", &n);
	memset(a, 0, sizeof(a));
	for (int i = 0; i < n; ++ i) {
		int x;
		scanf("%d", &x);
		while (x --) {
			int y;
			scanf("%d", &y);
			a[i] |= 1LL << y - 1;
		}
	}
	int result = 0;
	for (int j = 0; j < n; ++ j) {
		long long b = a[j] << 1;
		for (int i = 0; i < j; ++ i) {
			result += __builtin_parityll(b & (a[i] + (a[i] | ~b)));
		}
	}
	printf("%d\n", result);
	return 0;
}
