#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
// Problem: Runner and Sniper
// Author: Naoto Mizuno (not)
// Expected Status; AC

#include <cassert>
#include <complex>
#include <iomanip>
#include <iostream>

using namespace std;

class Validator {
private:
  bool unread;
  char prv;
  
  bool isSeparator(char c) {
    if (c == ' ') return true;
    if (c == '\n') return true;
    if (c == '\t') return true;
    return false;
  }
  
  char readChar() {
    if (unread) {
      unread = false;
      return prv;
    }
    return prv = getchar();
  }

  void back() {
    assert(unread == false);
    unread = true;
  }
  
  int readInt() {
    char c = readChar();
    long long n;
    if (c == '-') {
      c = readChar();
      assert('1' <= c && c <= '9');
      n = -(c - '0');
    } else {
      assert('0' <= c && c <= '9');
      n = c - '0';
    }
    if (n == 0) {
      assert(!isdigit(readChar()));
      back();
      return 0;
    }
    while (true) {
      c = readChar();
      if(!isdigit(c)) {
        back();
        break;
      }
      if (n > 0) n = n * 10 + c - '0';
      else n = n * 10 - (c - '0');
      assert((-1LL) << 31 <= n && n < (1LL << 31));
    }
    return n;
  }

  string readString() {
    string s;
    char c;
    while (!isSeparator(c = readChar())) s += c;
    back();
    return s;
  }
  
public:
  Validator() {
    unread = false;
  }
  
  ~Validator() {
    assert(readChar() == EOF);
  }
  
  int readInt(int a, int b) {
    int n = readInt();
    assert(a <= n && n <= b);
    return n;
  }

  const static int LOWER_CHAR = 1;
  const static int UPPER_CHAR = 2;
  const static int DIGIT_CHAR = 4;
  const static int SYMBOL_CHAR = 8;
  string readString(int flag, int a, int b) {
    string s = readString();
    assert(a <= (int)s.size() && (int)s.size() <= b);
    for (const auto& c : s) {
      if (islower(c)) {
        assert(flag & LOWER_CHAR);
      } else if (isupper(c)) {
        assert(flag & UPPER_CHAR);
      } else if (isdigit(c)) {
        assert(flag & DIGIT_CHAR);
      } else {
        assert(flag & SYMBOL_CHAR);
      }
    }
    return s;
  }
  
  void readSpace() {
    assert(readChar() == ' ');
  }
  
  void readEoln() {
    assert(readChar() == '\n');
  }
};

const int MIN_X = -1000;
const int MAX_X =  1000;
const int MIN_Y = -1000;
const int MAX_Y =  1000;
const int MIN_T =     0;
const int MAX_T =   359;
const int MIN_V =     1;
const int MAX_V =   100;

typedef long double Real;
typedef complex<Real> Point;

const Real PI = acos(-1);

// 平方根
inline Real sr(const Real& a) {
  return sqrt(max<Real>(a, 0));
}

// 円
struct Circle{Point c; Real r;};

// 点から円への接線 firstがp->c.cに対して左側
inline pair<Point, Point> tCP(const Circle& c, const Point& p) {
  Real d2 = norm(p - c.c);
  Real x = sr(d2 - c.r * c.r);
  Point h = c.c + (p - c.c) * (c.r * c.r / d2);
  Point w = (p - c.c) * (x * c.r / d2) * Point(0, 1);
  return make_pair(h - w, h + w);
}

int main() {
  Validator validator;
  int x = validator.readInt(MIN_Y, MAX_Y);
  validator.readSpace();
  int y = validator.readInt(MIN_Y, MAX_Y);
  validator.readSpace();
  int t = validator.readInt(MIN_T, MAX_T);
  validator.readSpace();
  int v = validator.readInt(MIN_V, MAX_V);
  validator.readEoln();
  Point p(x, y);
  p *= polar<Real>(1, -t * PI / 180);
  assert(p.real() < 0 || abs(p.imag()) > 1e-4);
  Real low = 0, high = 1e18;
  for (int i = 0; i < 200; ++i) {
    Real mid = (low + high) / 2;
    if (p.imag() < 0) p = conj(p);
    Real r = mid / (v * PI / 180);
    if (r > abs(p)) {
      high = mid;
      continue;
    }
    Point pp = tCP((Circle){Point(0), r}, p).second;
    Real a = arg(pp);
    if (a < 0) a += 2 * PI;
    if (abs(p - pp) / mid < a / (v * PI / 180)) high = mid;
    else low = mid;
  }
  cout << fixed << setprecision(15) << low << endl;
}
