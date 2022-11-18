#include <iostream>
#include <queue>
using namespace std;
const int inf = 400000;
struct node {
	int v;
	node* next;
	int dis;
	node(int x, int d, node* t) { v = x; dis = d; next = t; }
};
typedef node* link;
struct Graph {
	int vcnt;
	int ecnt;
	link* nodes;

}graph;
struct p {
	int dist;
	int k;
	bool operator<(const p& l) const {
		return dist > l.dist;
	}
};

int dis[40002] = { 0 ,0 };
int vis[40002] = { 0 };
priority_queue<p> min_dis;
void dij(int n) {
	int max = inf, k = 1;
	link t = graph.nodes[1];

	min_dis.push({ 0,1 });
	while(!min_dis.empty()){
		if (vis[min_dis.top().k]) {
			min_dis.pop();
			continue;
		}
		int min = min_dis.top().dist, k = min_dis.top().k;
		min_dis.pop();

		vis[k] = 1;
		t = graph.nodes[k];
		while (t->next) {
			int j = t->next->v;
			if (dis[j] > min + t->dis) {
				dis[j] = min + t->dis;
				min_dis.push({ dis[j],j });
			}
			t = t->next;
		}
	}
}
int main() {
	int n, m;
	cin >> n >> m;
	graph.vcnt = n;
	graph.ecnt = m;
	graph.nodes = new link[2 * n + 1];
	for (int i = 1; i <= 2 * n; i++) {
		graph.nodes[i] = new node(i, inf, NULL);
	}
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		graph.nodes[u]->next = new node(v, graph.nodes[u]->dis, graph.nodes[u]->next);
		graph.nodes[u]->dis = w;
		graph.nodes[v + n]->next = new node(u + n, graph.nodes[v + n]->dis, graph.nodes[v + n]->next);
		graph.nodes[v + n]->dis = w;
	}
	for (int i = 1; i <= n; i++) {
		graph.nodes[i]->next = new node(i + n, graph.nodes[i]->dis, graph.nodes[i]->next);
		graph.nodes[i]->dis = 0;
	}

	for (int i = 2; i < 40002; i++)dis[i] = inf;
	//dis[1 + n] = 0;
	dij(n);
	for (int i = n + 2; i <= 2 * n; i++) {
		cout << (dis[i] != inf ? dis[i] : -1) << " ";
	}

	return 0;
}