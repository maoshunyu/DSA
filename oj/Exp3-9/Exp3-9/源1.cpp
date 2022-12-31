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
		return a.value < b.value ? true : false;
	}
}le ;
struct gr {
	bool operator()(const f& a, const f& b) {
		return a.no < b.no ? true : false;
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
int find_max(){
    f max=foods[0];
    int index=0;
    for(int i=0;i<foods.size();i++){
        if(foods[i].value>=max.value){
            max=foods[i];
            index=i;
        }
    }
    return index;
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
	
	vector<f> res;
    int index=find_max();
	while (1) {
		if (recipe == 0)break;
		if (foods.size() == 0 || foods[index].value == 0) {
			cout << "-1";
			return 0;
		}
		res.push_back(foods[index]);
		recipe = (foods[index].food & recipe) ^ recipe;
		foods.erase(foods.begin()+index);
		for (auto it = foods.begin(); it != foods.end(); it++) {
			it->value = get_value(it->food);
		}
		index=find_max();
	}

	sort(res.begin(), res.end(),gr);
	for (int i=0; i<res.size()-1; i++) {
		cout << res[i].no << " ";
	}
	cout << res[res.size() - 1].no;
}