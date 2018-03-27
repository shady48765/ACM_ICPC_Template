#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdio>
#include <queue>
#include <set>
#include <map>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <algorithm>
#include <numeric>

#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define forn(i, n) for (int i = 0; i < (int)(n); ++i)
#define for1(i, n) for (int i = 1; i <= (int)(n); ++i)
#define ford(i, n) for (int i = (int)(n) - 1; i >= 0; --i)
#define fore(i, a, b) for (int i = (int)(a); i <= (int)(b); ++i)

using namespace std;

typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long i64;
typedef vector<i64> vi64;
typedef vector<vi64> vvi64;

template<class T>
bool uin(T &a, T b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}

template<class T>
bool uax(T &a, T b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

bool cmp(const string &s, const string &t) {
    return s.size() > t.size();
}

const int ALPHA = 26;

bool query(const string &s) {
    cout << "? " << s << endl;
    string t;
    cin >> t;
    return t == "YES";
}

string mergest(string s, string t) {
    vector<string> parts(1);
    forn(i, s.size()) parts.pb(string(1, s[i]));
    int i = 0;
    forn(j, t.size()) {
        while (1) {
            parts[i] += t[j];
            if (query(accumulate(all(parts), string()))) break;
            else {
                parts[i].resize(parts[i].size() - 1);
                ++i;
            }
        }
    }
    return accumulate(all(parts), string());
}

int main() {
    ios::sync_with_stdio(false);
    cout.precision(10);
    cout << fixed;

    vector<string> parts;
    forn(c, ALPHA) {
        string t;
        char cc = 'a' + c;
        while (1) {
            if (query(t + cc)) t += cc;
            else break;
        }
        parts.pb(t);
    }

    while (parts.size() > 1) {
        sort(all(parts), cmp);
        string s = parts.back();
        parts.pop_back();
        string t = parts.back();
        parts.pop_back();
        parts.pb(mergest(s, t));
    }
    cout << "! " << parts[0] << '\n';

#ifdef LOCAL_DEFINE
    cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
    return 0;
}
