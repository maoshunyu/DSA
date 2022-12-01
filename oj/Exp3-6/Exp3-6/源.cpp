#include <iostream>
#include <map>
#include <algorithm>
using namespace std;
bool cmp(const pair<string, int> a, const pair<string, int> b) {
	return a.second < b.second;
}
int main() {
	int n;
	map<string,int> map;
	cin >> n;
	while (n-- > 0) {
		int m;
		cin >> m;
		string s;
		getchar();
		while (m-- > 0) {
			s = "";
			char c=getchar();
			while ((c != ' ')&&(c!='\n')) {
				if ((c != 'l') && (c != 'L'))s += c;
				c = getchar();
			}
			if (s != "") {
				transform(s.begin(), s.end(), s.begin(), ::tolower);
				map[s]++;
			}
		}
	}
	
	cout << max_element(map.begin(), map.end(), cmp)->second;
}