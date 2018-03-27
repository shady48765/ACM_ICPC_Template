#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

bool check(const std::string &text, const std::string &pattern, bool unknown)
{
	if (pattern.empty()) {
		return true;
	}
	std::string str = pattern + '#' + text;
	int n = str.size();
	std::vector <int> fail(n, -1);
	for (int i = 0; i + 1 < n; ++ i) {
		int p = i;
		while (~p && fail[i + 1] == -1) {
			p = fail[p];
			if (str[p + 1] == str[i + 1]) {
				fail[i + 1] = p + 1;
			}
		}
	}
	std::vector <bool> match(n, false);
	match[(int)pattern.size() - 1] = true;
	for (int i = pattern.size(); i + unknown < (int)str.size(); ++ i) {
		if (~fail[i]) {
			match[i] = match[i] | match[fail[i]];
		}
		if (match[i]) {
			return true;
		}
	}
	return false;
}

const int MAX_ANS = 20;

int main()
{
	std::string source, target;
	std::cin >> source >> target;
	bool unknown = false;
	int result = 0;
	while (result < MAX_ANS && !check(source, target, unknown)) {
		result ++;
		int fb = 0;
		while (fb < (int)target.size() && target[fb] != 'b') {
			fb ++;
		}
		if (fb == (int)target.size()) {
			int nb = (int)target.size() >> 1;
			unknown |= (int)target.size() & 1;
			target = "";
			for (int _ = 0; _ < nb; ++ _) {
				target += 'a';
			}
		} else {
			std::string ntarget;
			for (int _ = 0; _ < fb >> 1; ++ _) {
				ntarget += 'a';
			}
			ntarget += 'b';
			for (int i = fb + 1; i < (int)target.size(); i += 2) {
				if (target[i] == 'b') {
					result = MAX_ANS;
					break;
				} else if (i + 1 >= (int)target.size()) {
					unknown = true;
				} else {
					ntarget += target[i + 1];
				}
			}
			target = ntarget;
		}
	}
	printf("%d\n", result >= MAX_ANS ? -1 : result);
	return 0;
}
