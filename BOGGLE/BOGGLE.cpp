#include <stdio.h>
#include <iostream>
using namespace std;

int size = 0;
int dir_y[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
int dir_x[8] = { -1, 0, 1, 1, 1, 0, -1, -1 };
char map[5][5] = { 0, };

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

bool adj_ok(int sy, int sx, bool DP[5][5]) {
	for (int d = 0; d < 8; d++) {
		int y = sy + dir_y[d];
		int x = sx + dir_x[d];
		if (y < 0 || y >= 5 || x < 0 || x >= 5)
			continue;
		if (DP[y][x] == 1)
			return true;
	}
	return false;
}


void init(bool DP[5][5]) {
	for (int y = 0; y < 5; y++) for (int x = 0; x < 5; x++) DP[y][x] = 1;
}

// dynamic programming approach
// O(10*25)
bool has_word_DP(int sy, int sx, char* word) {
	if (_str_len(word) == 0)	return true;

	int len = _str_len(word);
	bool DP1[5][5], DP2[5][5];
	bool(*cur)[5] = DP1, (*prev)[5] = DP2;
	init(DP1); init(DP2);

	// 01. DP approach : search for current word && prev adjcent prev word
	for (int i = 0; i < len; i++) {
		if (i % 2 == 0) {
			cur = DP1; prev = DP2;
		}
		else {
			cur = DP2; prev = DP1;
		}
		for (int y = 0; y < 5; y++) {
			for (int x = 0; x < 5; x++) {
				if (map[y][x] == word[len - 1 - i] && adj_ok(y, x, prev))
					cur[y][x] = 1;
				else
					cur[y][x] = 0;
			}
		}
	}

	// 02. check the last result is possible
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < 5; x++) {
			if (cur[y][x] == 1)
				return true;
		}
	}
	return false;
}

// brute force approach + recursive way
// O(8^25)
bool has_word_BruteForce(int y, int x, char* word) {
	if (_str_len(word) == 0)	return true;

	// 01. start case : search for all staring word
	if (y == -1 && x == -1) {
		for (int _y = 0; _y < 5; _y++) {
			for (int _x = 0; _x < 5; _x++) {
				if (word[0] == map[_y][_x] && has_word_BruteForce(_y, _x, word + 1))
					return true;
			}
		}
		return false;
	}

	// 02. recursive case
	int len = _str_len(word);
	for (int i = 0; i < 8; i++) {
		int new_y = y + dir_y[i];
		int new_x = x + dir_x[i];

		if (new_y < 0 || new_y >= 5
			|| new_x < 0 || new_x >= 5)
			continue;

		char c = map[new_y][new_x];
		if (c == word[0] && has_word_BruteForce(new_y, new_x, word + 1))
			return true;
	}
	return false;
}



int main() {
	freopen("BOGGLE\\test.txt", "r", stdin);
	char input[100] = { 0, };
	int TC;
	cin >> TC;
	for (int i = 0; i < TC; i++) {
		// get the map
		for (int _y = 0; _y < 5; _y++) {
			for (int _x = 0; _x < 5; _x++) {
				cin >> map[_y][_x];
			}
		}

		// check the input case
		int n_input;
		cin >> n_input;
		for (int j = 0; j < n_input; j++) {
			cin >> input;
			if (has_word_DP(-1, -1, input))
				cout << input << " YES" << endl;
			else
				cout << input << " NO" << endl;
		}
	}
	return 0;
}