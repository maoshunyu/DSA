#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned short u16;
u16 recipe = 0;
u16* foods;
int* dp[2];
int pre[65536], eat[65536];
int* name[2];int min(int& a, int& b) { return a < b ? a : b; }
int main() {
	int n, m;
	cin >> n >> m;
	foods = new u16[m];
	dp[0] = new int[65536];
	dp[1] = new int[65536];
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
		dp[0][j] =  0x3f3f3f3f;
		eat[j] = -1;
		pre[j] = -1;
	}
	dp[0][0] = dp[1][0] = 0;
	eat[0] = pre[0]= - 1;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j < 65536; j++) {
			int a = dp[(i - 1) % 2][j], b = 1 + dp[(i - 1) % 2][(foods[i - 1] & j) ^ j];
			if (a < b) {
				dp[i % 2][j] = a;
			}
			else {
				dp[i % 2][j] = b;
				pre[j] = (foods[i - 1] & j) ^ j;
				eat[j] = i - 1;
			}
			
		}
	}
	if (dp[m % 2][recipe] >= 0x3f3f3f3f) { cout << "-1"; return 0; }
	vector<int> res;
	int t = pre[recipe];
	int f = eat[recipe];
	while (t != -1) {
		res.push_back(f);
		f = eat[t];
		t = pre[t];
	}
	sort(res.begin(), res.end());
	for (auto it = res.begin(); it != res.end(); it++) {
		cout << *it << " ";
	}
}
