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

//Michał Glapa
#include<cstdio>
#include<set>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
#include<cstdlib>
#include<time.h>
#include<stack>
#include<cmath>
#include<iostream>
#include<cstring>
using namespace std;
#define ret return
#define FOR(i,j,k) for(int i=j;i<k;i++)
#define FORD(i,j,k) for(int i=j;i>=k;i--)
#define ll long long
#define pii  pair<int, int>
#define vi vector<int >
#define pb push_back
#define mp make_pair
#define make(n) int n; scanf("%d",&n)
#define st first
#define nd second
#define INF 2000000001
#define VAR(i,n) __typeof(n) i = (n)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();i++)
#define FORDEACH(i,c) for( VAR(i,(c).rbegin(),i!=(c).rend();i++)
#define REP(i,n) FOR(i,0,n)
#define ld long double
const long long INFLL = (ll)INF * (ll)INF;
const ld EPS = 10e-9;

#define MAXN 100007
struct node
{
    ll ex, in;
    node(){}
    node(ll ex, ll in) : ex(ex),in(in)
    {}

};
ll wynik=0;
vector<pair<int,ll> > graf[MAXN];
node t [MAXN];
int parent[MAXN];
int root=1;
void edge_update(int v)
{
    FOREACH(i,graf[v])
    {
        if(i->st!=parent[v])
        {
            ll tmp = min( t[i->st].ex - i->nd,2*t[i->st].in);
            if(tmp >0)
            {
                t[i->st].ex-=  2*((tmp+1)/2);
                t[i->st].in-= (tmp+1)/2;
                wynik+= (tmp+1)/2;
            }
            t[i->st].ex = min(t[i->st].ex,i->nd);
        }
    }
}
void resolve (int v)
{
    t[v].ex=0;
    t[v].in=0;
    edge_update(v);
    FOREACH(i,graf[v])
    {
        if(i->st != parent[v])
        {
            ll tmp_ex = t[v].ex;
            ll tmp_in = t[v].in;
            t[v].ex = tmp_ex + t[i->st].ex;
            ll k = min(tmp_ex,t[i->st].ex);
            t[v].in =k+min((tmp_ex-k)/2,tmp_in)+min((t[i->st].ex-k)/2,t[i->st].in);
            k--;
            t[v].in = max(t[v].in,k+min((tmp_ex-k)/2,tmp_in)+min((t[i->st].ex-k)/2,t[i->st].in));
        }
    }
}
ll get(int v)
{
    if(graf[v].size()==1)
        return wynik+t[v].ex;
    else
        return wynik+ t[v].in;
}
void dfs(int v,int p)
{
    FOREACH(i,graf[v])
    {
        if(i->st!=p)
        {
            parent[i->st]=v;
            dfs(i->st,v);
        }
    }
    if(graf[v].size()==1 && v!=root)
    {
        t[v].ex=INF;
        t[v].in=0;
    }
    else
        resolve(v);
}
int main()
{
    make(z);
    while(z--)
    {
        make(n);
        FOR(i,1,n+1)
        {
            graf[i].clear();
        }
        FOR(i,0,n-1)
        {
            make(a);
            make(b);
            make(c);
            graf[a].pb(mp(b,c));
            graf[b].pb(mp(a,c));
        }
        wynik=0;
        dfs(root,-1);
        printf(INT64 "\n",get(root));
    }
}

