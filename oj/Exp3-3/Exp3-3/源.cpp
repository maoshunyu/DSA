#include <vector>
#include <queue>
#include <string.h>
#include <stdio.h>
#pragma warning(disable:4996)

int N;
class Map {
public:
	int* map;
	Map(int size=0) {
		if (size == 0)return;
		map = new int[1 + size / 32];
		memset(map, 0, sizeof(int) * (1 + size / 32));
	}
	bool get(int& x, int& y) {
		return (map[(x * N + y) / 32] & (1 << (x * N + y) % 32)) >> (x * N + y) % 32;
	}
	void set1(int& x, int& y) {
		map[(x * N + y) / 32] |= 1 << ((x * N + y) % 32);
	}
	void set0(int& x, int& y) {
		map[(x * N + y) / 32] &= ~(1 << ((x * N + y) % 32));
	}
};
//short** map;
Map map, vis;
void dfs(int x,int y,int& count);
void dfs2(int x, int y);
int max_area = 0;
std::vector<int> starts;
struct lt 
{
	bool operator() (const int& a, const int& b) {
		return a / N > b / N || (a / N == b / N && a % N > b % N);
	}
};

std::priority_queue<int, std::vector<int>,lt> pq;
int main() {
	scanf("%d", &N);
	//map = new short[N];
	map = Map(N * N);
	vis = Map(N * N);
	bool all_zero = false;
	for (int i = 0; i < N; i++) {
		//map[i] = new short[N];
		for (int j = 0; j < N; j++) {
			int t;
			//cin >> map[i][j];
			scanf("%d", &t);
			if (t)map.set1(i, j);
			else map.set0(i, j);
			if (!all_zero && t)all_zero = true;
		}
	}
	if (!all_zero) {
		printf("-1");
		return 0;
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			int count = 0;
			dfs(i,j,count);
			if (count > 0) {
				if (count > max_area) {
					max_area = count;
					starts.clear();
					starts.push_back(i * N + j);
				}
				else if (count == max_area) {
					starts.push_back(i * N + j);
				}
			}

		}
	}
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			//map[i][j] &= ~2;
			vis.set0(i, j);
		}
	}
	printf("%d\n", max_area);
	for (auto it = starts.begin(); it != starts.end(); it++) {
		while (!pq.empty()) {
			printf("(%d,%d)", pq.top() / N, pq.top() % N);
			
			pq.pop();
		}
		if (it != starts.begin()) { printf("\n"); }
		dfs2(*it / N, *it % N);
	}
	while (!pq.empty()) {
		printf("(%d,%d)", pq.top() / N, pq.top() % N);
		pq.pop();
	}

	return 0;
}

void dfs(int x,int y,int& count) {
	if (!map.get(x,y) || vis.get(x, y)) { return; }
	vis.set1(x,y);
	if (x < N - 1)dfs(x + 1, y,count);
	if (y < N - 1)dfs(x, y + 1, count);
	if (x > 0)dfs(x - 1, y, count);
	if (y > 0)dfs(x, y - 1, count);
	if ((x < N - 1) && (y < N - 1))dfs(x + 1, y + 1, count);
	if ((x < N - 1) && (y > 0))dfs(x + 1, y - 1, count);
	if ((x > 0) && (y < N - 1))dfs(x - 1, y + 1, count);
	if ((x > 0) && (y > 0))dfs(x - 1, y - 1, count);
	count++;
}
void dfs2(int x, int y) {
	/*if (!(map[x][y] & 1) || (map[x][y] & 2)) { return; }
	map[x][y] |= 2;*/
	if (!map.get(x, y) || vis.get(x, y)) { return; }
	vis.set1(x, y);
	if (x < N - 1)dfs2(x + 1, y);
	if (y < N - 1)dfs2(x, y + 1 );
	if (x > 0)dfs2(x - 1, y);
	if (y > 0)dfs2(x, y - 1);
	if ((x < N - 1) && (y < N - 1))dfs2(x + 1, y + 1);
	if ((x < N - 1) && (y > 0))dfs2(x + 1, y - 1);
	if ((x > 0) && (y < N - 1))dfs2(x - 1, y + 1);
	if ((x > 0) && (y > 0))dfs2(x - 1, y - 1);
	pq.push(x*N+y);
}
