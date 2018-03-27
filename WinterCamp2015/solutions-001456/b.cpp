#include <stdlib.h>
#include <string.h>
#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 6;

const char L = 'L';
const char R = 'R';
const char U = 'U';
const char D = 'D';

int board[N * N];

void makeMove(int line, char dir, int dist){
	if(dir == D){dir = U; dist = N - dist;}
	if(dir == R){dir = L; dist = N - dist;}
	printf("%d %c %d\n", line + 1, dir, dist);
	while(dist--)
		for(int i = 0; i + 1 < N; i++)
			if(dir == U)
				swap(board[i * N + line], board[(i + 1) * N + line]);
			else
				swap(board[line * N + i], board[line * N + i + 1]);
}

void toCorner(int i, int j){
	if(i == 0 && j == 0) {
		return;
	} else if(i == 0){
		makeMove(0, L, j); makeMove(0, U, 1);
		makeMove(0, R, j); makeMove(0, D, 1);
	} else if(j == 0){
		makeMove(0, U, i); makeMove(0, L, 1);
		makeMove(0, D, i); makeMove(0, R, 1);
	} else {
		makeMove(0, R, j), makeMove(j, U, i);
		makeMove(0, L, j), makeMove(j, D, i);
	}
}

const char * solved = "abcdefghijklmnopqrstuvwxyz0123456789";

int main(){
	int inv = 0;
	
	for(int i = 0; i < N * N; i++){
		char c;
		scanf("\n%c", &c);
		while(solved[board[i]] != c) board[i]++;
		for(int j = 0; j < i; j++)
			if(board[j] > board[i]) inv++;
	}

	if(inv & 1) makeMove(0, L, 1);
	for(int s = 2 * N; s > 0; s--)
		for(int i = max(s - N + 1, 0); i <= min(N-1, s); i++){
			int j = s - i;
			int k = 0;
			while(board[k] != i * N + j) k++;
			toCorner(k / N, k % N);
			toCorner(i, j);
			toCorner(i, j);
		}
}