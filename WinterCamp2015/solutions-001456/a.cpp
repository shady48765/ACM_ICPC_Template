#include <bits/stdc++.h>
#define FWD(a,b,c) for(int a=(b); a<(c); ++a)

using namespace std;

int n, k, x, y;
vector<int> V;

int main() {
	int z;
	scanf("%d", &z);
	while(z--){
		scanf("%d %d %d %d", &n, &k, &x, &y);
		V.clear();
		FWD(i,0,n){
			int a;
			scanf("%d", &a);
			V.push_back(a);
		}
		if(n < k+2){printf("NO\n"); continue;}
		sort(V.begin(), V.end());
		bool ok = 1;
		if(x < y){
			if((k && V[n-k] < y) || V[n-k-2] < x)
				ok = 0;
		}else{
			if(V[n-2] < x || (k && V[n-k-2] < y))
				ok = 0;
		}
		printf(ok?"YES\n":"NO\n");
	}
}
