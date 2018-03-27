#include <stdio.h>
#include <string.h>
/*
  Problem: Meister's morning is early
  Solution by: Masahiko Nishida

  Memoize DFS
  O(2^N * N^2 * (N - K)!)
*/

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <numeric>
#include <vector>
#include <tuple>
#include <unordered_map>
using namespace std;

constexpr int MAX_N = 16;
const string NG = "~";

int n, k;
string histories[MAX_N];

vector<pair<int, int>> table[MAX_N][1 << 6];
map<tuple<int, int, int>, string> memo;

bool check(const string &current_history, const string &next_history) {
	int prev = -1;
	for(const auto &c : next_history) {
		const int tmp = current_history.find(c);
		if(prev > tmp) return false;
		prev = tmp;
	}
	return true;
}

void init() {
	vector<unordered_map<char, int>> enc(n);
	vector<unordered_map<int, char>> dec(n);
	for(int i = 0; i < n; ++i) {
		for(char c = 'A'; c < 'A' + n; ++c) {
			if(histories[i].find(c) == string::npos) {
				const int idx = enc[i].size();
				enc[i].emplace(c, idx);
				dec[i].emplace(idx, c);
			}
		}
	}

	for(int last_id = 0; last_id < n; ++last_id) {
		vector<int> order(n - k);
		iota(begin(order), end(order), 0);
		do {
			int tmp = 0;
			for(const auto &e : order) {
				tmp = (tmp << 2) | e;
			}

			auto &next = table[last_id][tmp];
			string current_history(histories[last_id]);
			reverse(begin(current_history), end(current_history));
			for(const auto &e : order) {
				current_history += dec[last_id][e];
			}

			for(int next_id = 0; next_id < n; ++next_id) {
				if(last_id == next_id || !check(current_history, histories[next_id])) continue;

				int buf = 0;
				for(const auto &c : current_history) {
					if(enc[next_id].count(c)) {
						buf = (buf << 2) | enc[next_id][c];
					}
				}
				next.emplace_back(next_id, buf);
			}
		} while(next_permutation(begin(order), end(order)));
	}
}

string dfs(int used, int last_id, int order) {
	if(used == (1 << n) - 1) return "";

	const tuple<int, int, int> t{used, last_id, order};
	if(memo.count(t)) return memo[t];
	string res = NG;

	res = NG;
	for(const auto &e : table[last_id][order]) {
		const int next_id = e.first;
		const int next_order = e.second;

		if(used & (1 << next_id)) continue;
		const auto x = dfs(used | (1 << next_id), next_id, next_order);
		if(x != NG) {
			res = char('A' + next_id) + x;
			break;
		}
	}
	memo.emplace(t, res);
	return res;
}

int main() {
	cin.tie(nullptr);
	ios::sync_with_stdio(false);

	cin >> n >> k;

	for(int i = 0; i < n; ++i) {
		cin >> histories[i];
	}

	init();

	string ans = NG;
	for(int first = 0; first < n; ++first) {
		vector<int> order(n - k);
		iota(begin(order), end(order), 0);

		do {
			int tmp = 0;
			for(const auto &e : order) {
				tmp = (tmp << 2) | e;
			}
			const auto x = dfs(1 << first, first, tmp);
			if(x != NG) ans = min(ans, char('A' + first) + x);
		} while(next_permutation(begin(order), end(order)));

		if(ans != NG) break;
	}

	assert(ans != NG);
	cout << ans << endl;

	return EXIT_SUCCESS;
}
