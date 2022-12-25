#include <iostream>
#include <cstring>
using namespace std;
typedef unsigned short u16;
u16 recipe = 0;
u16* foods;
int* dp[2];
int* name[2];
int min(int& a, int& b) { return a < b ? a : b; }
int main() {
	int n, m;
	cin >> n >> m;
	foods = new u16[m];
	dp[0] = new int[65536];
	dp[1] = new int[65536];
	name[0] = new int[65536];
	name[1] = new int[65536];
	u16* temp = new u16[m];
	memset(foods, 0, sizeof(u16) * m);
	for (int i = 0; i < m; i++) {
		int t;
		cin >> t;
		temp[i] = t;
	}
	for (int i = 0; i < n; i++) {
		int t;
		cin >> t;
		recipe |= 1 << t;
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < temp[i]; j++) {
			int t;
			cin >> t;
			foods[i] |= 1 << t;
		}
	}
	delete[] temp;
	for (int j = 1; j < 65536; j++) {
		dp[0][j] = name[0][j] = 0x3f3f3f3f;
	}
	dp[0][0] = dp[1][0] = 0;
	name[0][0] = name[1][0] = 0;
	int* path = new int[m];
	memset(path, 0, sizeof(int) * m);
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j < 65536; j++) {
			dp[i % 2][j] = min(dp[(i - 1) % 2][j], 1 + dp[(i - 1) % 2][(foods[i - 1] & j) ^ j]);
			if (j == recipe)path[i - 1] = dp[i % 2][j];
		}
	}
	if (dp[m % 2][recipe] >= 0x3f3f3f3f) { cout << "-1"; return 0; }
	cout << name[m % 2][recipe];
}
