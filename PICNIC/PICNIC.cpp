#include <stdio.h>
#include <iostream>
using namespace std;

void init(int map[10][10]) {
	for (int y = 0; y < 10; y++) for (int x = 0; x < 10; x++) map[y][x] = 0;
}

int _str_len(char* arr) {
	int len = 0;
	while (true) {
		if (arr[len] == 0)
			break;
		else
			len++;
	}
	return len;
}

int N, M;
int adj[10][10];

void input() {
	scanf("%d %d", &N, &M);
	init(adj);
	for (int i = 0; i < M; i++) {
		int x, y;
		scanf("%d %d", &x, &y);
		if (y < x)
			adj[y][x] = 1;
		else
			adj[x][y] = 1;
	}
}

int visit[10] = { 0, };
int ok_num = 0;

// Exhaustive search in recursive way
// O(N^N)
int unit_solve_rec(int s) {
	int result = 0;
	// base case
	if (ok_num == N)
		return 1;

	// search case
	if (visit[s] == 1)	// for visited case
		return unit_solve_rec(s + 1);

	for (int e = s + 1; e < N; e++) {
		if (e != s && adj[s][e] == 1 && visit[e] == 0) {
			visit[s] = visit[e] = 1;
			ok_num += 2;

			result += unit_solve_rec(s + 1);

			visit[s] = visit[e] = 0;
			ok_num -= 2;
		}
	}
	return result;
}

int solve() {
	return unit_solve_rec(0);
}

int main() {
	freopen("PICNIC_test.txt", "r", stdin);
	int TC;
	cin >> TC;
	for (int i = 0; i < TC; i++) {
		// input
		input();

		// check the input case
		cout << solve() << endl;
	}
	return 0;
}