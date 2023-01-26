#include <iostream>
#pragma warning(disable:4996)
#include <string.h>
using namespace std;
struct info {
	char data[5];
	long pos;
};
using str = char[5];

long m, n;
str* a, * b;
void input2() {
	long suma = m * (m - 1) / 2, sumb = n * (n - 1) / 2;
	info* ha = new info[m];
	a = new str [m];
	getchar();
	for (long i = 0; i < m; i++) {
		cin >> ha[i].data >> ha[i].pos;
		suma -= ha[i].pos;
	}
	suma--;
	long starta = suma;
	for (long i = 0; i < m; i++) {
		strcpy(a[i] ,ha[starta].data);
		starta = ha[starta].pos;
	}
	delete[]ha;
	ha = new info[n];
	b = new str [n];
	getchar();
	for (long i = 0; i < n; i++) {
		cin >> ha[i].data >> ha[i].pos;
		sumb -= ha[i].pos;
	}
	sumb--;

	long startb = sumb;
	for (long i = 0; i < n; i++) {
		strcpy(b[i] ,ha[startb].data);
		startb = ha[startb].pos;
	}
	delete[]ha;
	ha = NULL;
}
int main() {
	cin >> m >> n;
	input2();


	int i = 0;
	bool flag = true;
	int min = m > n ? n : m;
	int index = 0;


	for (; i != min; i++) {
		int xa = m - i - 1, xb = n - i - 1;
		int r = strcmp(a[xa], b[xb]);
		if (i == 0 && r != 0) {
			cout << "-1";
			flag = false;
			break;
		}

		if (r != 0) {
			index = min - i;
			break;
		}
		if (i == min - 1) {
			i++;
			break;
		}
	}
	if (flag) {
		cout << index << endl;
		if (min == m) {
			while (index != min) { cout << a[index] << " "; index++; }
		}
		else {
			while (index != min) {
				cout << b[index] << " "; index++;
			}
		}

	}
}