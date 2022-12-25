#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned short u16;
struct f {
	u16 food;
	int value;
	int no;

};
struct le {
	bool operator()(const f& a, const f& b) {
		return a.value > b.value;
	}
}le;
struct gr {
	bool operator()(const f& a, const f& b) {
		return a.no < b.no;
	}
}gr;
u16 recipe = 0;
vector<f> foods;
int get_value(u16 food) {
	int count = 0;
	food = food & recipe;
	for (int i = 0; i < 16; i++) {
		if (((food >> i) & 1) == 1)  count++;
	}
	return count;
}


int main() {
	int n, m;
	cin >> n >> m;
	u16* temp = new u16[m];
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
	u16 recipe_c = recipe;
	for (int i = 0; i < m; i++) {
		foods.push_back({ 0,0,i });
		for (int j = 0; j < temp[i]; j++) {
			int t;
			cin >> t;
			foods[i].food |= 1 << t;
		}
		foods[i].value = get_value(foods[i].food);
	}
	delete[] temp;
	sort(foods.begin(), foods.end(), le);
	vector<f> res;
	while (1) {
		if (recipe == 0)break;
		if (foods.size() == 0 || foods[0].value == 0) {
			cout << "-1";
			return 0;
		}
		res.push_back(foods[0]);
		recipe = (foods[0].food & recipe) ^ recipe;
		foods.erase(foods.begin());
		for (auto it = foods.begin(); it != foods.end(); it++) {
			it->value = get_value(it->food);
		}
		sort(foods.begin(), foods.end(), le);
	}
	recipe = recipe_c;

	for (auto it = res.begin(); it != res.end();) {
		u16 t = 0;
		for (auto jt = res.begin(); jt != res.end(); jt++) {
			if (jt == it)continue;
			t |= jt->food;
		}
		if (((t & recipe) ^ recipe) == 0) {
			it=res.erase(it);
		}
		else {
			it++;
		}
	}
	
	
	sort(res.begin(), res.end(), gr);
	for (int i = 0; i < res.size(); i++) {
		cout << res[i].no << " ";
	}
}