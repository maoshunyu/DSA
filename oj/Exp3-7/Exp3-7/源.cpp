#include <iostream>
#include <cmath>
#include <string.h>
#include <vector>
#include <algorithm>
#define eps 0.00001
using namespace std;
double* H=NULL;
void mul(int n, double A[], double B[], double C[]) {
    double* t = new double[n * n];
    memset(t, 0, sizeof(double) * n * n);
    for (int i = 0; i < n; ++i) {
        for (int k = 0; k < n; ++k) {
            double s = A[i * n + k];
            for (int j = 0; j < n; ++j)
                t[i * n + j] += s * B[k * n + j];
        }
    }
    memcpy(C, t, sizeof(double) * n * n);
    delete[] t;
}

void trans(int n,double* M) {
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            if (j > i) {
                double temp = M[i*n+j];
                M[i * n + j] = M[j * n + i];
                M[j * n + i] = temp;
            }
        }
    }
}
void hess(int n, int j, double* M) {
    double alpha = 0;
    double vTv = 0;
    for (int i = j + 1; i < n; i++) {
        alpha += M[i * n + j] * M[i * n + j];
    }
    if (abs(alpha) < eps)return;
    alpha = sqrt(alpha);
    double* v = new double[n];
    memset(v, 0, sizeof(double) * n);
    for (int i = j + 2; i < n; i++) {
        v[i] = M[i * n + j];
        vTv += v[i] * v[i];
    }
    for (int i = 0; i < j+1; i++) {
        v[i] = 0;
    }
    if (M[(j + 1) * n + j] < 0)
        v[j + 1] = M[(j + 1) * n + j] - alpha;
    else
        v[j + 1] = M[(j + 1) * n + j] + alpha;
    vTv += v[j + 1] * v[j + 1];

    for (int i = j; i < n; i++) {
        double vTu = 0;
        for (int k = j; k < n; k++) {
            vTu += v[k] * M[k * n + i];
        }
        vTu = 2 * vTu / vTv;
        for (int k = 0; k < n; k++) {
            M[k * n + i] -= vTu * v[k];
        }
    }

    for (int i = 0; i < n; i++) {
        double vTu = 0;
        for (int k = j; k < n; k++) {
            vTu += v[k] * M[i * n + k];
        }
        vTu = 2 * vTu / vTv;
        for (int k = 0; k < n; k++) {
            M[i * n + k] -= vTu * v[k];
        }
    }

    delete[]v;
}
void givens(int n, double* M) {
    double* G = new double[n * n];
    for (int i = 0; i < n - 1;i++) {
        memset(G, 0, sizeof(double) * n * n);
        for (int j = 0; j < n; j++)G[j * n + j] = 1;
        double r = sqrt(M[(i + 1) * n + i] * M[(i + 1) * n + i] + M[i * n + i] * M[i * n + i]);
        double cos = M[i * n + i] / r, sin = M[(i + 1) * n + i] / r;
        G[i * n + i] = G[(i + 1) * n + i + 1] = cos;
        G[i * n + i + 1] = sin;
        G[i * n + i + n] = -sin;
        //mul(n, G, M, M);
        for (int j = 0; j < n; j++) {
            double g1 = M[i * n + j], g2 = M[(i + 1) * n + j];
            M[i * n + j] = cos * g1 + sin * g2;
            M[(i + 1) * n + j] = cos * g2 - sin * g1;
        }
        trans(n,G);
        //mul(n, H, G, H);
        for (int j = 0; j < n; j++) {
            double g1 = H[j * n + i], g2 = H[j * n + i+1];
            H[j * n + i] = cos * g1 + sin * g2;
            H[j * n + i+1] = cos * g2 - sin * g1;
        }
    }
    delete[] G;
}

int main() {
    int n;
    cin >> n;
    double* M = new double[n * n];
    memset(M, 0, sizeof(double) * n * n);
    H = new double[n * n];
    memset(H, 0, sizeof(double) * n * n);
    for (int i = 0; i < n; i++)H[i * n + i] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            double x;
            cin >> x;
            M[i * n + j] = x;
        }
    }
    for (int i = 0; i < n-2; i++) {
        hess(n, i, M);
    }
    for (int i = 0; i < 1000;i++) {
        givens(n, M);
        mul(n, M, H, M);
        memset(H, 0, sizeof(double) * n * n);
        for (int i = 0; i < n; i++)H[i * n + i] = 1;

    }
    vector<double> a;
    for (int i = 0; i < n; i++) {
        a.push_back(M[i * n + i]);
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; i++) {
        printf("%.2f\n", a[i]);
    }
    //print(M,n);
}