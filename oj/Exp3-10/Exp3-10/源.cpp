#include <bitset>
#include <iostream>
#include <queue>
#include <stack>
#include <string.h>
#include <vector>
using namespace std;

struct Point {
    short x;
    short y;
    char dir; // 1 2 3 4

};

int lx = 0, ly = 0;
const int N = 250000;
bitset<N * 4> vis;
bitset<N> map;
bitset<N*4> preL;
bitset<N * 4> preU;
stack<short> road;
/*
00  ->  F
01  ->  F2
10  ->  L
11  ->  R
*/

Point start, mid, endp;

void bfs(Point a, Point b) {
    queue<Point> q;
    q.push(a);
    while (!q.empty()) {
        Point t = q.front();
        q.pop();

        vector<int> v({ 1, 0, 3, 2 });

        for (auto&& i : v) {
            short nx = t.x, ny = t.y;
            char nz = t.dir;
            switch (i) {
            case 0:
                switch (t.dir) {
                case 1:
                    ny--;
                    break;
                case 2:
                    nx--;
                    break;
                case 3:
                    ny++;
                    break;
                case 4:
                    nx++;
                    break;
                default:
                    break;
                }
                break;
            case 1:
                switch (t.dir) {
                case 1:
                    ny -= 2;
                    break;
                case 2:
                    nx -= 2;
                    break;
                case 3:
                    ny += 2;
                    break;
                case 4:
                    nx += 2;
                    break;
                default:
                    break;
                }
                break;
            case 2:
                nz = (nz + 1) > 4 ? 1 : (nz + 1);
                break;
            case 3:
                nz = (nz - 1) < 1 ? 4 : (nz - 1);
                break;
            default:
                break;
            }
            if (nx >= 0 && nx < lx && ny >= 0 && ny < ly &&
                map[ny * lx + nx] == 0 &&
                vis[(nz - 1) * lx * ly + ny * lx + nx] == 0) {
                if (i != 1) {
                    preL[(nz - 1) * lx * ly + ny * lx + nx] = i&1;
                    preU[(nz - 1) * lx * ly + ny * lx + nx] = i >>1 & 1;
                    vis[(nz - 1) * lx * ly + ny * lx + nx] = 1;
                    q.push({ nx, ny, nz });
                }
                else {
                    if (((nx - t.x == 2) &&
                        map[ny * lx + nx - 1] == 0) ||
                        ((nx - t.x == -2) &&
                            map[ny * lx + nx + 1] == 0) ||
                        ((ny - t.y == 2) &&
                            map[(ny - 1) * lx + nx] == 0) ||
                        ((ny - t.y == -2) &&
                            map[(ny + 1) * lx + nx] == 0)) {
                        preL[(nz - 1) * lx * ly + ny * lx + nx] = i & 1;
                        preU[(nz - 1) * lx * ly + ny * lx + nx] = i >> 1 & 1;
                        vis[(nz - 1) * lx * ly + ny * lx + nx] = 1;
                        q.push({ nx, ny, nz });
                    }
                }
            }
        }

    }
    short x = b.x, y = b.y;
    char z = b.dir;
    while (x >= 0 || y >= 0 || (z >= 1 && z <= 4)) {
        if (x == a.x && y == a.y && z == a.dir)
            break;
        short d0 = preL[(z - 1) * lx * ly + y * lx + x];
        short d1 = preU[(z - 1) * lx * ly + y * lx + x];
        road.push(d0+d1*2);
        switch (d0 + d1 * 2) {
        case 0:
            switch (z) {
            case 1:
                y++;
                break;
            case 2:
                x++;
                break;
            case 3:
                y--;
                break;
            case 4:
                x--;
                break;
            default:
                break;
            }
            break;
        case 1:
            switch (z) {
            case 1:
                y += 2;
                break;
            case 2:
                x += 2;
                break;
            case 3:
                y -= 2;
                break;
            case 4:
                x -= 2;
                break;
            default:
                break;
            }
            break;
        case 2:
            z = (z - 1) < 1 ? 4 : (z - 1);
            break;
        case 3:
            z = (z + 1) > 4 ? 1 : (z + 1);
            ;
            break;
        default:
            break;
        }
    }
    preL.reset();
    preU.reset();
    vis.reset();
}
int main() {
    cin >> lx >> ly;
    vis.reset();
    map.reset();
    for (int j = 0; j < ly; j++) {
        for (int i = 0; i < lx; i++) {
            int t;
            cin >> t;
            map[j * lx + i] = t;
        }
    }
    char t;
    cin >> start.x >> start.y >> t;
    start.dir = t - 48;
    cin >> mid.x >> mid.y >> t;
    mid.dir = t - 48;
    cin >> endp.x >> endp.y >> t;
    endp.dir = t - 48;
    bfs(mid, endp);
    bfs(start, mid);
    cout << road.size() << endl;
    while (!road.empty()) {
        auto s = road.top();
        switch (s) {
        case 0:
            cout << "F" << endl;
            break;
        case 1:
            cout << "F2" << endl;
            break;
        case 2:
            cout << "L" << endl;
            break;
        case 3:
            cout << "R" << endl;
            break;
        }
        road.pop();

    }

}
