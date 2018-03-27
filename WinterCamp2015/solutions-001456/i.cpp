#include <stdlib.h>
#include <algorithm>
#include <iostream>
#include <deque>
#include <string.h>
#include <cstdio>
using namespace std;

#define MAX_N 1000000

char circle[MAX_N];
int circle_n, w, h; 

char getchild(int pos) {
	pos += 8 * circle_n;
	return circle[pos % circle_n];
}

int alg() {
	int max_size = 0;
	deque<int> seq;
	seq.push_front(0);
	int size = 0, Dc = 0;
	for (int pos = 2*circle_n-1; pos >= 0; --pos) {
		if (getchild(pos) == 'G') {
			++(seq.front());
			seq.push_front(0);
			++Dc;
		}
		else {
			int f = seq.front();
			seq.pop_front();
			if (!seq.empty()) {
				seq.front() += 1 + f;
			}
			else {
				seq.push_front(f + 1);
			}
		}
		++size;
		
		while (size > 0) {
			int to_skip = h - w + 1;
			int swaps = (to_skip < seq.size()) ? (seq.size() - to_skip + 1) / 2 : 0;
			int w1 = w - size + Dc - swaps;
			bool is_last_swapped = (to_skip < seq.size() && (seq.size() - to_skip)%2 == 1 && seq.back() == 1);
			if (w1 > 0 || w1 == 0 && (getchild(pos+size-1) == 'B' || is_last_swapped)) break;
			if (getchild(pos+size-1) == 'G') --Dc;
			--size;
			if (--seq.back() == 0) {
				if (seq.size() > 1) seq.pop_back();
			}
		}
		
		int size1 = size;
		if (size1 > circle_n) size1 = circle_n;
		if (max_size < size1) {
			max_size = size1;
		} 
	} 
	
	return max_size;
}

int main() {
	int z;
	scanf("%d", &z);
	while (z--) {
		scanf("%d%d%s", &w, &h, circle) ;
		if (w > h) {
			int tmp = w;
			w = h;
			h = tmp;
		}
		circle_n = strlen(circle);
		int wyn =  alg();
        printf("%d\n", wyn);
	}
}
