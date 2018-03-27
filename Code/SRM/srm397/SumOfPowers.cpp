
// BEGIN CUT HERE

// END CUT HERE
#line 6 "SumOfPowers.cpp"
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
#define MOD 1000000007
using namespace std;


class SumOfPowers
{
        public:
        int value(int n, int k)
        {

        }

// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); }
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { int Arg0 = 5; int Arg1 = 1; int Arg2 = 15; verify_case(0, Arg2, value(Arg0, Arg1)); }
	void test_case_1() { int Arg0 = 4; int Arg1 = 2; int Arg2 = 30; verify_case(1, Arg2, value(Arg0, Arg1)); }
	void test_case_2() { int Arg0 = 13; int Arg1 = 5; int Arg2 = 1002001; verify_case(2, Arg2, value(Arg0, Arg1)); }
	void test_case_3() { int Arg0 = 123456789; int Arg1 = 1; int Arg2 = 383478132; verify_case(3, Arg2, value(Arg0, Arg1)); }

// END CUT HERE

};

// BEGIN CUT HERE
int main()
{
        SumOfPowers ___test;
        ___test.run_test(-1);
        return 0;
}
// END CUT HERE
