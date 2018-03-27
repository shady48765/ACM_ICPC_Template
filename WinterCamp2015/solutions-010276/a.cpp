#include <string.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

int main(void){
	double d;
	cin >> d;
	double ans = d * sqrt(2.0);
	for(int i=1;i<=10;i++) if(d >= i && d < sqrt(i*i+1.0)) ans = max(ans, i + 1.0);
	printf("%.12f\n", ans);
	return 0;
}
