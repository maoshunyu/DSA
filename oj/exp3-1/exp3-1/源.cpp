#include <iostream>
#pragma warning(disable:4996)
const float eps = 0.001f;
bool isCoplanar(float a[3], float b[3], float c[3]) {
	float det = a[0] * (b[1] * c[2] - b[2] * c[1]) - a[1] * (b[0] * c[2] - b[2] * c[0]) + a[2] * (b[0] * c[1] - b[1] * c[0]);
	return (det >= -eps) && (det <= eps);
}
int main() {
	int N;
	scanf("%d", &N);
	float point[4][3] = { 0 };
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < 3; j++)
			scanf("%f", &point[i % 4][j]);
		if (i > 3) {
			float vec[3][3] = { 0 };
			for (int j = 0; j < 3; j++) {
				vec[j][0] = point[j + 1][0] - point[j][0];
				vec[j][1] = point[j + 1][1] - point[j][1];
				vec[j][2] = point[j + 1][2] - point[j][2];
			}
			if (!isCoplanar(vec[0], vec[1], vec[2])) {
				std::cout << i;
				break;
			}
		}
		else if (i == 3) {
			float vec[3][3] = { 0 };
			for (int j = 0; j < 3; j++) {
				vec[j][0] = point[j + 1][0] - point[j][0];
				vec[j][1] = point[j + 1][1] - point[j][1];
				vec[j][2] = point[j + 1][2] - point[j][2];
			}
			if (!isCoplanar(vec[0], vec[1], vec[2])) {
				float extra[3] = { 0 };
				for (int j = 0; j < 3; j++)
					scanf("%f", &extra[j]);
				for (int i = 0; i < 4; i++) {
					for (int j = 0; j < 2; j++) {
						vec[j][0] = point[(j + 1 + i) % 4][0] - point[(j + i) % 4][0];
						vec[j][1] = point[(j + 1 + i) % 4][1] - point[(j + i) % 4][1];
						vec[j][2] = point[(j + 1 + i) % 4][2] - point[(j + i) % 4][2];
					}
					vec[2][0] = extra[0] - point[(i + 2) % 4][0];
					vec[2][1] = extra[1] - point[(i + 2) % 4][1];
					vec[2][2] = extra[2] - point[(i + 2) % 4][2];
					if (isCoplanar(vec[0], vec[1], vec[2])) {
						switch (i) {
						case 3:
							std::cout << "2";
							goto end;
						case 2:
							std::cout << "1";
							goto end;
						case 1:
							std::cout << "0";
							goto end;
						case 0:
							std::cout << "3";
							goto end;
						}
					}
				}
			}
		}
	}


	end:
	return 0;
}