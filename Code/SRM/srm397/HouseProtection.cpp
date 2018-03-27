#line 6 "HouseProtection.cpp"
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <fstream>
#include <numeric>
#include <iomanip>
#include <bitset>
#include <list>
#include <stdexcept>
#include <functional>
#include <utility>
#include <ctime>
using namespace std;


class HouseProtection
{
public:
    int X1[55],Y1[55],X2[55],Y2[55];
    int G[55][55];
    int p1[55],p2[55];
    bool vis[55];
    int n,m;
    bool findpath(int v)
    {
        for(int i=1;i<=m;i++)
            if(G[v][i]&&!vis[i])
        {
            vis[i]=true;
            if(p2[i]<0||findpath(p2[i]))
            {
                p2[i]=v;
                p1[v]=i;
                return true;
            }
        }
        return false;
    }
    int check(double R)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(((X1[i]-X2[j])*(X1[i]-X2[j])+(Y1[i]-Y2[j])*(Y1[i]-Y2[j]))<4.0*R*R-1e-3)
                    G[i][j]=1;
                else
                    G[i][j]=0;
        for(int i=1;i<=n;i++)
            p1[i]=-1;
        for(int j=1;j<=m;j++)
            p2[j]=-1;
        int cnt=m+n;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                if(G[i][j]&&(p1[i]<0&&p2[j]<0))
                {
                    p1[i]=j;p2[j]=i;cnt--;
                }
        for(int i=1;i<=n;i++) if(p1[i]<0)
        {
            memset(vis,0,sizeof(vis));
            if(findpath(i)) cnt--;
        }
        return cnt;
    }
    double safetyFactor(vector <int> possibleXForBlue, vector <int> possibleYForBlue, vector <int> possibleXForRed, vector <int> possibleYForRed, int R)
    {
        n=possibleXForBlue.size();
        m=possibleXForRed.size();
        for(int i=1;i<=n;i++)
            X1[i]=possibleXForBlue[i-1],Y1[i]=possibleYForBlue[i-1];
        for(int i=1;i<=m;i++)
            X2[i]=possibleXForRed[i-1],Y2[i]=possibleYForRed[i-1];
        double r=check(R)*R*R;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
            {
                double rr=sqrt((X1[i]-X2[j])*(X1[i]-X2[j])+(Y1[i]-Y2[j])*(Y1[i]-Y2[j]))/2.0;
                if(rr<=R)
                r=max(r,check(rr)*rr*rr);
            }
        return atan(1.0)*4.0*r;
    }
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const double &Expected, const double &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arr0[] = { 0, 4 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0, 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 2, 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = { 2, -1 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 1; double Arg5 = 9.42477796076938; verify_case(0, Arg5, safetyFactor(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_1() { int Arr0[] = { 1 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 1 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 1 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = { 1 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 5; double Arg5 = 78.53981633974483; verify_case(1, Arg5, safetyFactor(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_2() { int Arr0[] = { 0 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 0 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 100 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = { 0 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 51; double Arg5 = 15707.963267948966; verify_case(2, Arg5, safetyFactor(Arg0, Arg1, Arg2, Arg3, Arg4)); }
	void test_case_3() { int Arr0[] = { 23, 29, 29, 35 }; vector <int> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arr1[] = { 77, 79, 75, 77 }; vector <int> Arg1(Arr1, Arr1 + (sizeof(Arr1) / sizeof(Arr1[0]))); int Arr2[] = { 26, 26, 32 }; vector <int> Arg2(Arr2, Arr2 + (sizeof(Arr2) / sizeof(Arr2[0]))); int Arr3[] = { 78, 76, 76 }; vector <int> Arg3(Arr3, Arr3 + (sizeof(Arr3) / sizeof(Arr3[0]))); int Arg4 = 3; double Arg5 = 113.09733552923255; verify_case(3, Arg5, safetyFactor(Arg0, Arg1, Arg2, Arg3, Arg4)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        HouseProtection ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
