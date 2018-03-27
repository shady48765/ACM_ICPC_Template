#include <cmath>
#include <cstdio>

int main()
{
	int x[3], y[3];
	for (int i = 0; i < 3; ++ i) {
		scanf("%d%d", x + i, y + i);
	}
	printf("%.9f\n", hypot(x[0] - x[2], y[0] - y[2]) + 2 * hypot(x[1] - x[2], y[1] - y[2]));
	return 0;
}
