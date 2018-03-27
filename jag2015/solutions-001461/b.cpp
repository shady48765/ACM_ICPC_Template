//JAG_SpringContest15
//CardGameStrategy JudgeSolution(By Nakasuka)
#include<vector>
#include<cmath>
#include<map>
#include<cstdlib>
#include<iostream>
#include<sstream>
#include<fstream>
#include<string>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<set>
#include<stack>
#include<bitset>
#include<functional>
#include<ctime>
#include<queue>
#include<deque>
#include<complex>

const int MIN_NK = 1;
const int MAX_NK = 600;

const int MIN_AB = 0;
const int MAX_AB = 600 * 300;

const int MIN_X = 0;
const int MAX_X = 300;

using namespace std;
#define pb push_back
#define pf push_front
typedef long long lint;
typedef complex<double> P;
#define mp make_pair
#define fi first
#define se second
typedef pair<int,int> pint;
#define All(s) s.begin(),s.end()
#define rAll(s) s.rbegin(),s.rend()
#define REP(i,a,b) for(int i=a;i<b;i++)
#define rep(i,n) REP(i,0,n)
#define maxn MAX_NK
#define maxb MAX_AB
short dp[2][maxn+10][maxb+10];
short pre[maxn+10][maxb+10];
bool ok[maxb+10];
bool out[maxn+10];
int x[maxn+10];
int le[maxb+10],ri[maxb+10];
int main()
{
	int n,a,b,K,inf=1145141919,c=0;short inf2=25252;
	cin>>n>>K>>a>>b;
	rep(i,n) cin>>x[i];
	rep(i,K) c+=x[i];
	
	//DPフェイズ
	rep(i,n+5) rep(j,maxb+5) dp[0][i][j]=dp[1][i][j]=inf2;
	dp[0][K-1][c]=-1;
	memset(pre,0,sizeof(pre));
	REP(i,K-1,n){
		//F1からの推移
		rep(j,maxb+1){
			//if(dp[1][i][j]>=inf2) continue;
			//cout<<1<<' '<<i<<' '<<j<<' '<<dp[1][i][j]<<' '<<pre[1][i][j]<<endl;
			int ub=K-1;if(i>0) ub=min(ub,(int)dp[1][i-1][j]);
			REP(k,dp[1][i][j]+1,ub+1){
				if(dp[0][i][j-x[k]]>k){
					dp[0][i][j-x[k]]=(short)k;pre[i][j-x[k]]=1;
				}
			}
		}
		
		//F0からの推移
		rep(j,maxb+1){
			//if(dp[0][i][j]>=inf2) continue;
			//cout<<0<<' '<<i<<' '<<j<<' '<<dp[0][i][j]<<' '<<pre[0][i][j]<<endl;
			if(dp[0][i+1][j]>dp[0][i][j]){
				dp[0][i+1][j]=dp[0][i][j];pre[i+1][j]=0;
			}
			dp[1][i+1][j+x[i+1]]=min(dp[1][i+1][j+x[i+1]],dp[0][i][j]);
		}
	}
	
	//Alice,Bobが選ぶ数字を調べるフェイズ
	memset(ok,false,sizeof(ok));
	rep(i,maxb+1){
		if(dp[0][n][i]<inf2) ok[i]=true;
	}
	//if(ok[180000]) cout<<'a'<<endl;else cout<<'b'<<endl;
	/*rep(i,b+1){
		if(ok[i]) cout<<"ok"<<i<<endl;
	}*/
	le[0]=ri[maxb]=inf;if(ok[maxb]) ri[maxb]=0;if(ok[0]) le[0]=0;
	rep(i,maxb){
		le[i+1]=le[i]+1;
		if(ok[i+1]) le[i+1]=0;
	}
	for(int j=maxb;j>0;j--){
		ri[j-1]=ri[j]+1;
		if(ok[j-1]) ri[j-1]=0;
	}
	//cout<<ri[0]<<' '<<le[0]<<' '<<ri[180000]<<' '<<le[180000]<<endl;
	int al=a,di,bo;
	REP(i,a,b+1){
		if(min(le[i],ri[i])>min(le[al],ri[al])) al=i;
	}
	di=min(le[al],ri[al]);
	if(al>=di && ok[al-di]) bo=al-di;else bo=al+di;
	//cout<<bo<<endl;
	
	//復元フェイズ
	memset(out,false,sizeof(out));
	rep(i,K) out[i]=true;
	for(int i=n;i>=K;i--){
		if(pre[i][bo]){
			//cout<<'a'<<i<<endl;
			out[dp[0][i][bo]]=false;
			bo+=x[dp[0][i][bo]];
			out[i]=true;
			bo-=x[i];
		}
		//cout<<bo<<endl;
	}
	vector<int> ret;
	rep(i,n){if(out[i]) ret.pb(i+1);}
	cout<<al<<endl;
	rep(i,K){
		cout<<ret[i];
		if(i<K-1) cout<<' ';else cout<<endl;
	}
}
