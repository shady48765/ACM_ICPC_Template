#include <cstdio>
#include <cstring>

const int N = 200000;

int a[N], b[N];

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; ++ i) {
		scanf("%d", a + i);
	}
	for (int k = 30; k >= 0; -- k) {
		int parity = 0;
		for (int i = 0; i < n; ++ i) {
			parity ^= a[i] >> k & 1;
		}
		if (!parity) {
			int nn = 0;
			for (int i = 0; i < n; ) {
				b[nn] = a[i];
				int j = i + 1;
				while (b[nn] >> k & 1) {
					b[nn] ^= a[j ++];
				}
				nn ++;
				i = j;
			}
			if (nn >= m) {
				n = nn;
				for (int i = 0; i < n; ++ i) {
					a[i] = b[i];
				}
			}
		}
	}
	int result = 0;
	for (int i = 0; i < n; ++ i) {
		result |= a[i];
	}
	printf("%d\n", result);
	return 0;
}
