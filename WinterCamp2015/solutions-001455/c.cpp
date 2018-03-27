#include <stdlib.h>
#include <string.h>
#include <algorithm>
// obroty.cpp
#include<cstdio>
#include <cstdio>

typedef long long ll;


int main() {
    ll n, k;
    scanf("%lli %lli",&n, &k);
    if(!k) {
        printf("0\n");
        return 0;
    }
    if(n==2 && k == 1) {
        printf("1\n0 1\n");
        return 0;
    }
    if(k == 1) {
        printf("2\n");
        printf("%lli %lli\n",0ll, n-k-1ll);
        printf("%lli %lli\n",0ll,n-1ll);
        return 0;
    }
    if(k == n-1) {
        printf("2\n");
        printf("%lli %lli\n",1ll,n-1ll);
        printf("%lli %lli\n",0ll, n-1ll);
        return 0;
    }
    if(k == 2) {
        printf("2\n");
        printf("%lli %lli\n",0ll, n-2ll);
        printf("%lli %lli\n",1ll,n-1ll);
        return 0;
    }
    if(k == n-2ll) {
        printf("2\n");
        printf("%lli %lli\n",1ll,n-1ll);
        printf("%lli %lli\n",0ll,n-2ll);
        return 0;
    }

    printf("3\n");
    printf("%lli %lli\n", 0ll, n-1ll);
    printf("%lli %lli\n", 0ll, k-1ll);
    printf("%lli %lli\n", k, n-1ll);
    
}
