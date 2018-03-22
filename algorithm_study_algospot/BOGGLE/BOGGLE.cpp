#include <stdio.h>
#include <iostream>
using namespace std;

int size = 0;
int dir_y[8] = { 1, 1, 1, 0, -1, -1, -1, 0 };
int dir_x[8] = { -1, 0, 1, 1, 1, 0, -1, -1};
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

bool has_word(int y, int x, char* word) {
	if (_str_len(word) == 0)	return true;

	// 01. start case : search for all staring word
	if (y == -1 && x == -1) {
		for (int _y = 0; _y < 5; _y++) {
			for (int _x = 0; _x < 5; _x++) {
				if (word[0] == map[_y][_x] && has_word(_y, _x, word + 1))
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
		if (c == word[0] && has_word(new_y, new_x, word + 1))
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
			if (has_word(-1, -1, input))
				cout << "POSSIBLE" << endl;
			else
				cout << "IMPOSSIBLE" << endl;
		}
	}
	return 0;
}