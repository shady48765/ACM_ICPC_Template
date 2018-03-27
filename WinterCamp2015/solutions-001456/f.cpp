//Jan Gwinner

#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <cstdio>
#include <cstring>
#include <cmath>




#define REP(i,n) for(int i=0;i<(n);++i)
#define SIZE(c) ((int)((c).size()))
#define FOR(i,a,b) for (int i=(a); i<(b); ++i)
#define FORD(i,a,b) for (int i=((int)(a))-1; i>=(b); --i)
#define FWD(i,a,b) for (int i=(a); i<(b); ++i)
#define BCK(i,a,b) for (int i=(a); i>(b); --i)
#define ALL(u) (u).begin(),(u).end()


#define st first
#define nd second   
#define inf 2000000000
#define x first
#define y second
#define pb push_back
#define mp make_pair
#define N (1<<20)
#define milion 1000000
#define oneoneone ios_base::sync_with_stdio(false)



using namespace std;

const int rozmiar_kubelka = 356;

typedef long long ll;
typedef double K;
typedef pair<int, int > pii;
typedef pair<ll, ll> pll;
typedef unsigned long long ull;
typedef pair<ll, int > pli;
typedef pair<int, ll > pil;



/*ll inverse(ll a, ll n) {
    ll t = 0ll, newt = 1ll;
    ll r = n, newr = a;
    while(newr!=0ll) {
        ll quotient = r/newr;
        tie(t, newt) = mp(newt, t - quotient * newt );
        tie(r, newr) = mp(newr, r - quotient * newr );
    }
    if(r > 1ll) return 0;
    if(t < 0ll) t+=n;
    t%=n;
    return t;
}*/

ll gcd(ll a, ll b){
    while(a&&b)a>b?a%=b:b%=a;
    return a+b;
}

ll lcm(ll a, ll b) {
    ll c = gcd(a,b);
    a/=c;
    b/=c;
    return a*b;
} 

int m;

int n;

map< vector<int > , int > S; 

void rozbijNaCykle(vector<int> &vec, vector<vector<int >  > &res) {
    vector<bool > used;
    used.resize(vec.size());
    for(int i = 0; i < n; i++) {
        
        if(!used[i]) {
            vector<int > seq;
            seq.pb(i);
            used[i] = true;
            int j = vec[i];
            while(j!=i) {
                seq.pb(j);
                used[j]= true;
                j = vec[j];
            
            }
            res.pb(seq);
        }
    }
}



void sprawdz() {
    ll res[n];
    REP(i,n+1) res[i] = -1;
    vector<int > nowa(n);

    vector<int > akt(n);
    REP(i,n) {
        scanf("%d", &akt[i]);
        akt[i]--;
    }
    vector<vector<int > > rozb;
    rozbijNaCykle(akt, rozb);
    
    for(int i = 0; i < rozb.size(); i++ ){
        vector<pii > ktory;
        if(rozb[i].size() == 1 ) {
            nowa[rozb[i][0]] = rozb[i][0];
            continue;
        }
        for(int j = 0; j < rozb[i].size(); j++) {
              if(gcd(j,rozb[i].size()) !=1)continue;
              ktory.pb(mp(rozb[i][j], j));
        }
        int aktual = 1;
        sort(ktory.begin(), ktory.end());
        for(int zz = 0 ; zz < ktory.size(); zz ++ ) {
            int j = ktory[zz].y;
            int ok = 1;
            for(int k = 2; k<=rozb[i].size(); k++) {
                if(res[k]!=-1 && rozb[i].size()%k == 0 && j%k!=res[k]) {
                    ok = 0;
                    break;
                }
            }
            if(ok) {
                aktual = j;
                break;
            }
        }
        for(int j = 2; j<=rozb[i].size(); j++) {
            if(rozb[i].size()%j == 0 ) {
                res[j] = (aktual)%j;
            }
        }
        for(int j = 0; j  < rozb[i].size(); j++) {
            nowa[rozb[i][j]] = rozb[i][(j+aktual)%rozb[i].size()];
        }
    }
    int xd = S[nowa];
    S[nowa]++;
    printf("%d\n", xd);
}



int main() {
    int z; scanf("%d", &z); while(z--) {
        S.clear();
        scanf("%d%d", &n, &m);
        for(int i = 0; i < m; i++) {
            sprawdz();
        }
    } 
    return 0;
}









































