#include <stdlib.h>
#include <string.h>
//atak.cpp - wzorcowka
#include <cstdio>
#include <string>
#include <algorithm>
#include <vector>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <queue>
#include <set>
#include <map>

#define fru(j,n) for(int j=0;j<n;++j)
#define tr(it,x) for(typeof(x.begin()) it=x.begin();it!=x.end();++it)
#define x first
#define y second
#define pb push_back

using namespace std;

typedef pair<int,int> pii;
typedef long long LL;
const int MAXN = 200003;
const int MAXT=(1<<19)+5;

vector<int> D[MAXN],V[MAXN],VT[MAXN],ND[MAXN],WD[MAXN],PRE,Q;
int tin[MAXN],tout[MAXN],par[MAXN],scc[MAXN],SCC,ct;
// 0<=scc[u]<SCC  - numer scc w ktorej jest u

int dfs_scc(int u)
{
	tin[u]=ct++;
	Q.push_back(u);
	int m=tin[u];
	tr(it,V[u]) if(scc[*it]==-1)
	{
		if(tin[*it]!=-1) m=min(m,tin[*it]);
		else m=min(m,dfs_scc(*it));
	}
	if(m==tin[u])
	{
		vector<int> R;
		do{
			R.push_back(Q.back());
			Q.pop_back();
		}
		while(R.back()!=u);
		++SCC;
		tr(it,R) scc[*it]=SCC;
	}
	return m;
}

void dfs(int u,vector<int> *W){
	tin[u]=PRE.size();
	PRE.pb(u);
	tr(it,W[u]) if(scc[u]!=scc[*it]) continue;
	else if(tin[*it]==-1){
		dfs(*it,W);
		par[tin[*it]]=tin[u];
		D[tin[u]].pb(tin[*it]);
	}
	else {
		ND[tin[*it]].pb(tin[u]);
		WD[tin[u]].pb(tin[*it]);
	}
	tout[tin[u]]=PRE.size()-1;
}

int X[MAXN];
bool kryt[MAXN];

int tree[MAXT],BAS;
int get_min(int u){
	int ret=MAXN;
	for(u+=BAS;u;u/=2) {
		ret=min(ret,tree[u]);
	}
	return ret;
}
int pocz,kon,val;
inline void set_min(int e,int beg_seg,int end_seg){
	if(pocz<=beg_seg && end_seg<=kon){
		tree[e]=min(tree[e],val);
		return;
	}
	int m=(beg_seg+end_seg)/2;
	if(m>=pocz) set_min(2*e  ,beg_seg,m  );
	if(m<kon)   set_min(2*e+1,m+1,end_seg);
}
int czas;
int vis[MAXN];
int check_scc(int u,int nie,vector<int> *W){ //u jest prawdziwym numerem
	vis[u]=czas;
	int ccount=1;
	tr(it,W[u])if(scc[*it]==scc[u] && *it!=nie && vis[*it]!=czas) ccount+=check_scc(*it,nie,W);
	return ccount;
}
void solve_scc(int root){
	int r;
	fru(o,2){
		if(o==1) tr(it,PRE) tin[*it]=-1;
		fru(i,PRE.size()) D[i].clear(),ND[i].clear(),WD[i].clear();
		PRE.clear();
		if(o==1) dfs(root,V);
		else dfs(root,VT);
		assert(PRE[0]==root);
		r=PRE.size();
		fru(i,r) assert(i==0 || PRE[i]!=root);
		if(r<=2) return;
		BAS=1;
		while(BAS<r) BAS*=2;
		fru(i,2*BAS+1) tree[i]=MAXN;
		for(int u=r-1;u>=0;--u){
			X[u]=min(par[u],get_min(u));
			tr(it,ND[u]){
				if(*it<u) X[u]=min(X[u],*it);
				else X[u]=min(X[u],get_min(*it));
			}
			pocz=u,kon=tout[u],val=X[u];
			set_min(1,0,BAS-1);
			if(X[u]==par[u]) kryt[PRE[par[u]]]=1;
		}
	}
	int g=PRE[1],nie=PRE[0];
	czas++;
	int mm=check_scc(g,nie,V);
	czas++;
	mm=min(mm,check_scc(g,nie,VT));
	kryt[nie]=mm!=r-1;
}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	fru(i,m){
		int a,b;
		scanf("%d%d",&a,&b);
		V[a-1].pb(b-1);
		VT[b-1].pb(a-1);
	}
	fru(i,n) scc[i]=tin[i]=-1;
	fru(i,n) if(tin[i]==-1) dfs_scc(i);
	fru(i,n) tin[i]=-1;
	fru(i,n) if(tin[i]==-1) solve_scc(i);
//	printf("%d\n",SCC);
	fru(i,n) printf("%s\n",kryt[i]?"YES":"NO");
	return 0;
}
