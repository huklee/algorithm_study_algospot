#include <stdio.h>
#include <iostream>
using namespace std;

int N, M;
int clock[16];
int wind[16];

// convert the clock into wind number
int c2w(int c) {
	return (12 - c) / 3;
}

int cc(int c) {
	if (c < 0)
		return 4 + c;
}

void init(int arr[16]) {
	for (int i = 0; i < 16; i++)
		arr[i] = 0;
}

void input() {
	for (int i = 0; i < 16; i++) {
		scanf("%d", &clock[i]);
		
	}
}

int sw[10][16] = { {1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
				   {0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,0},
				   {0,0,0,0,1,0,0,0,0,0,1,0,0,0,1,1},
				   {1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0},
				   {0,0,0,0,0,0,1,1,1,0,1,0,1,0,0,0},
				   {1,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
				   {0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,1},
				   {0,0,0,0,1,1,0,1,0,0,0,0,0,0,1,1},
				   {0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0},
				   {0,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0}};

int solve() {
	// get the wind number
	wind[4] = c2w(clock[8]);
	wind[1] = c2w(clock[11]);
	wind[9] = c2w(clock[13]);
	wind[2] = cc(c2w(clock[10]) - wind[4]);
	wind[3] = cc(c2w(clock[7]) - wind[1] - wind[4]);
	wind[7] = cc(c2w(clock[6] - wind[4] - wind[3]));
	wind[8] = cc(c2w(clock[5] - wind[3] - wind[7] - wind[9]));
	wind[6] = cc(c2w(clock[3] - wind[1] - wind[8] - wind[9]));
	wind[5] = cc(c2w(clock[14] - wind[2] - wind[6] - wind[7]));
	wind[0] = cc(c2w(clock[1] - wind[8]));

	// get the clock & verify the clock possibility
	for (int c = 0; c < 10; c++) {
		for (int w = 0; w < 16; w++)
			clock[c] += wind[w] * 3;
		if ((clock[c] % 3) % 4 != 0)
			return -1;
	}

	// return the numbers of the all wind number
	int sum = 0;
	for (int w = 0; w < 16; w++)
		sum += wind[w];
	return sum;
}

int main()
{
	freopen("CLOCKSYNC_test.txt", "r", stdin);
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