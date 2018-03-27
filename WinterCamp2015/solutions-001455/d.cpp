#include <stdlib.h>
#include <string.h>
#include <algorithm>
#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define INT64 "%I64d"
#else
#define INT64 "%lld"
#endif

#if ( _WIN32 || __WIN32__ || _WIN64 || __WIN64__ )
#define UNS64 "%I64u"
#else
#define UNS64 "%llu"
#endif
//denominacja.cpp - wzorcowka
/*
	Denominacje
	rozwiązanie O(1)
	Piotr Jagiełło 2014
*/

#include <cstdio>
#define MOD 1000000007LL
using namespace std;
typedef long long int lld;
lld sumakw(lld n)
{
	n%=MOD;
	lld wyn=(n*(n+1))%MOD;
	wyn=(wyn*(2*n+1))%MOD;
	return wyn;
}
lld suma(lld n)
{
	n%=MOD;
	return (n*(n+1))%MOD;
}
int main()
{
	lld n;
	scanf(INT64,&n);
	n/=5;
    lld k=n%5;
    lld w=n/5;
    lld wyn=(25*sumakw(w))%MOD;
    wyn=(wyn+30*(k+2)*suma(w))%MOD;
    wyn=(wyn+6*(w%MOD+1)*(k*k+4*(k+1)))%MOD;
	lld odj=((w+1)/2)*6;
	if(k%2==1 && w%2==0)odj+=6;
	odj%=MOD;
	wyn=(wyn-odj+MOD)%MOD;
	wyn=(wyn*41666667)%MOD;
	
	printf(INT64 "\n",wyn);
}
