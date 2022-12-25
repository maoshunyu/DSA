#include <complex>
#include <iostream>
#include <cmath>
using namespace std;
const double pi = 3.14159265358979323;

void fft(complex<double>* x, int size) {
	if (size <= 1)return;
	complex<double>* e = new complex<double>[size / 2];
	complex<double>* o = new complex<double>[size / 2];
	for (int i = 0; i < size; i += 2) {
		e[i / 2] = x[i];
	}
	for (int i = 1; i < size; i += 2) {
		o[i / 2] = x[i];
	}
	fft(e, size / 2);
	fft(o, size / 2);
	for (int i = 0; i < size / 2; i++) {
		double t = i * 2 * pi / size;
		complex<double> wn = o[i] * complex<double>(cos(t), -sin(t));
		x[i] = e[i] + wn;
		x[i + size / 2] = e[i] - wn;
	}
	delete[]e;
	delete[] o;
}
void ifft(complex<double>* x, int size) {
	if (size <= 1)return;
	complex<double>* e = new complex<double>[size / 2];
	complex<double>* o = new complex<double>[size / 2];
	for (int i = 0; i < size; i += 2) {
		e[i / 2] = x[i];
	}
	for (int i = 1; i < size; i += 2) {
		o[i / 2] = x[i];
	}
	ifft(e, size / 2);
	ifft(o, size / 2);
	for (int i = 0; i < size / 2; i++) {
		double t = i * 2 * pi / size;
		complex<double> wn = o[i] * complex<double>(cos(t), sin(t));
		x[i] = e[i] + wn;
		x[i + size / 2] = e[i] - wn;
	}
	delete[]e;
	delete[] o;
}
int main() {
	int N, M;
	cin >> N >> M;
	int n = N + M - 1;
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	n += 1;
	complex<double>* y = new complex<double>[n];
	complex<double>* h = new complex<double>[n];
	for (int i = 0; i < N + M - 1; i++) {
		double t;
		cin >> t;
		y[i] = t;
	}
	for (int i = 0; i < M; i++) {
		double ht;
		cin >> ht;
		h[i] = ht;
	}
	for (int i = M; i < n; i++) {
		h[i] = 0;
	}
	for (int i = M + N - 1; i < n; i++) {
		y[i] = 0;
	}
	fft(y, n);
	fft(h, n);
	for (int i = 0; i < n; i++) {
		y[i] = y[i] / h[i];
	}

	ifft(y, n);
	for (int i = 0; i < n; i++) {
		y[i] /= n;
	}
	bool no = false;
	for (int i = 0; i < N; i++) {
		if (y[i].real() < 0) {
			no = true;
			break;
		}
	}
	if (!no) {
		for (int i = 0; i < N; i++) {
			printf("%.4f ", y[i].real());
			no = false;
		}
	}
	else cout << N;
	return 0;
}