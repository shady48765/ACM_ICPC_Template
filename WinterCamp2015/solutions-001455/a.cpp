#include <stdlib.h>
#include <string.h>
// hard-rno.cpp (correct and fast)
/*
 * Rafał Nowak, 2014-03-09
 */ 
#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
#include<queue>
#include<cmath>
//#define debug(...) fprintf(stderr, __VA_ARGS__);
#define debug
using namespace std;

typedef long double real;

const int N = 1000, M = 1000;
const real EPS = 1.0e-12, EPS2 = 1.0e-10, EPS3 = 1.0e-11, INF = 1.0e+15L;

int n,m, s,t, c[N+M+2][N+M+2],dist[N+M+2],start[N+M+2];
real f[N+M+2][N+M+2], cf[N+M+2][N+M+2], cost[N+1], cost_2[N+1];

real dfs(int u, real K) {
 	//debug("dfs(%d,%.6Lf) dist=%d\n", u, K, dist[u]);
	if (u==t || K<EPS) return K;
	real ans = 0.0;
	for (int v=start[u]; v<=t; v++) {
		if ( dist[v]==dist[u]+1 && cf[u][v]>EPS ) 	{
			real ile = dfs( v, min(K,cf[u][v]) );
			cf[u][v] -= ile;
			cf[v][u] += ile;
			ans += ile;
			K -= ile; // dalej próbujemy zwiększyć przepływ o K-ile
			if (K<EPS) break;
		}
		start[u]++;
	}
 	//debug("dfs(%d)=%Lf\n", u, ans);
	return ans;
}

bool bfs() {
	for (int u=s; u<=t; u++) dist[u] = -1;
	queue<int> Q; Q.push(s); dist[s] = 0;
	while (!Q.empty()) 	{
		int u = Q.front(); Q.pop();
		for (int v=s; v<=t; v++) {
			// można chodzić tylko po krawędziach o własności cf[u][v]>0
			if (dist[v]==-1 && cf[u][v]>EPS) {
				dist[v] = dist[u]+1;
				Q.push(v);
			}
		}
	}
	return dist[t]!=-1; // czy udało się dojść do t?
}

void bfs_rev() {
	for (int u=s; u<=t; u++) dist[u] = -1;
	queue<int> Q; Q.push(t); dist[t] = 0;
	while (!Q.empty()) 	{
		int v = Q.front(); Q.pop();
		for (int u=s+1; u<=t; u++) { // uwaga nie wolno nam wejść pod prąd do samego źródła
			// można chodzić tylko po krawędziach o własności cf[u][v]>0
			if (dist[u]==-1 && cf[u][v]>EPS2) {
				dist[u] = dist[v]+1;
				Q.push(u);
			}
		}
	}
}

real maxflow() {
	real flow = 0.0, inc = 1.0;
	while (bfs() && inc>EPS) {
		for (int u=s; u<=t; u++) start[u]=s;
		inc = dfs(s,INF);
		flow += inc;
	}
	debug("maxflow()=%Lf = %Le\n", flow ,flow);
	return flow;
}

void solve() {
	vector<int> Q;
	scanf("%d %d", &n, &m); s=0; t=n+m+1;
	for (int u=1; u<=n; u++) scanf("%Lf", &cost[u]);
	for (int u=s; u<=t; u++) for (int v=s; v<=t; v++) f[u][v] = c[u][v] = 0.0;
	for (int u=1; u<=n; u++) c[s][u] = 1.0;
	for (int u=1; u<=n; u++) for (int v=1; v<=m; v++) scanf("%d", &c[u][n+v]);
	for (int v=1; v<=m; v++) c[n+v][t] = 1.0;
	
	// wyznaczamy sieć residualną
	// c[u][v] = przepustowość krawędzi u -> v,  f[u][v] = aktualny przepływ
	for (int u=s; u<=t; u++) for (int v=s; v<=t; v++) cf[u][v] = c[u][v]-f[u][v];
	
	// obliczamy max_flow
	const real max_flow = maxflow();
//	fprintf(stderr, "maximum flow = %Lg\n", max_flow);

	// zerujemy przepływ; szukamy takiego o najmniejszym koszcie
	for (int u=s; u<=t; u++) for (int v=s; v<=t; v++) f[u][v] = 0.0;
	
	// Szukamy max przepływu tylko przez wierzchołki o zerowym koszcie
	for (int u=1; u<=n; u++) if (cost[u]!=0) c[s][u]=0; // ustawiamy zerową przepustowość, jeśli był niezerowy koszt
	for (int u=s; u<=t; u++) for (int v=s; v<=t; v++) cf[u][v] = c[u][v]-f[u][v];
	real sum_flow = maxflow();
	for (int u=s; u<=t; u++) for (int v=s; v<=t; v++) f[u][v] = c[u][v]-cf[u][v];

	// poprawiamy przepustowości do lewych wierzchołków
	for (int u=1; u<=n; u++) c[s][u]=1;
	
	while ( sum_flow + 1.0e-8 < max_flow )
	{
		debug("sum_flow = %Lg\n", sum_flow);
		real b=2.0; // binary search
		while ( EPS3 < b ) {
			real x = b/2;
			debug("b=%Lg=%Le,  x=%Lg=%Le\n",b,b,x,x);
			// wyznaczamy sieć residualną
			for (int u=s; u<=t; u++) for (int v=s; v<=t; v++) cf[u][v] = c[u][v]-f[u][v];
			// wyznaczamy lewe wierzchołki, z których można dojść do t w sieci residualnej
			Q.clear(); bfs_rev(); for (int u=1; u<=n; u++) if ( cf[s][u]>EPS && dist[u]!=-1 ) { Q.push_back(u); debug("Q contains %d (cf=%Lg)\n", u, cf[s][u]); }
			if ( Q.empty() ) break;
			for (unsigned int i=0; i<Q.size(); i++) if ( cost[Q[i]] ) x=min(x,cf[s][Q[i]]*cost[Q[i]]); 
			debug("x = %Lg\n", x);
			// zmniejszamy przepustowości krawędzi w Q na x
			// uwaga na zerowe koszty;
			for (unsigned int i=0; i<Q.size(); i++) if ( cost[Q[i]] ) cf[s][Q[i]] = x/cost[Q[i]];
			real flow = maxflow();
			bool all = true; for (unsigned int i=0; i<Q.size(); i++) if ( cost[Q[i]] && cf[s][Q[i]] > EPS3 ) { all=false; break; }
			if ( all ) {
				debug("Increased ...\n");
				vector<real> oldf( Q.size() ); for (unsigned int i=0; i<Q.size(); i++) oldf[i] = f[s][Q[i]];
				for (int u=s; u<=t; u++) for (int v=s; v<=t; v++) f[u][v] = c[u][v]-cf[u][v];
				for (unsigned int i=0; i<Q.size(); i++) f[s][Q[i]] = cost[Q[i]] ? (oldf[i] + x/cost[Q[i]]) : c[s][Q[i]];
	// 			for (int u=1; u<=n; u++) { debug("flow[s][%d]=%Lf\n", u,f[s][u]); }
				sum_flow += flow;
				debug("sum_flow = %Lg\n", sum_flow);
				b = 2*b;
			}
			else b=x;
		}
		if ( Q.empty() ) break;
	}
	real ans = 0.0, flow = 0.0;
	for (int u=1; u<=n; u++) { ans += cost[u] * f[s][u] * f[s][u]; debug("flow[%2d]=%Lg\n", u, f[s][u]); flow += f[s][u]; }
//	fprintf(stderr, "maxflow = %Lg\n", flow);
	printf("%.6Lf\n", ans);
}

int main() { int iii=0, TTT=1; //scanf("%d", &TTT); 
	while(TTT--) { debug("Test case=%d\n", ++iii); solve(); } return 0; }
