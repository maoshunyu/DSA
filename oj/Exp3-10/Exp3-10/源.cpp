#include <bitset>
#include <iostream>
#include <queue>
#include <stack>
#include <string.h>
#include <vector>
using namespace std;

typedef struct Point {
    int x;
    int y;
    int dir; // 1 2 3 4
    bool operator==(Point &rhs) {
        return x == rhs.x && y == rhs.y && dir == rhs.dir;
    }
};
typedef bitset<2> bit2;

int lx = 0, ly = 0;
const int N = 250000;
bitset<N * 4> map, vis;
bit2 pre[N * 4];
stack<bit2> road;
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
        if (t == b)
            break;
        vector<int> v({1, 0, 3, 2});

        for (auto &&i : v) {
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
                map[(nz - 1) * lx * ly + ny * lx + nx] == 0 &&
                vis[(nz - 1) * lx * ly + ny * lx + nx] == 0) {
                if (i != 1) {
                    pre[(nz - 1) * lx * ly + ny * lx + nx] = i;
                    vis[(nz - 1) * lx * ly + ny * lx + nx] = 1;
                    q.push({nx, ny, nz});
                } else {
                    if (((nx - t.x == 2) &&
                         map[(nz - 1) * lx * ly + ny * lx + nx - 1] == 0) ||
                        ((nx - t.x == -2) &&
                         map[(nz - 1) * lx * ly + ny * lx + nx + 1] == 0) ||
                        ((ny - t.y == 2) &&
                         map[(nz - 1) * lx * ly + (ny - 1) * lx + nx] == 0) ||
                        ((ny - t.y == -2) &&
                         map[(nz - 1) * lx * ly + (ny + 1) * lx + nx] == 0)) {
                        pre[(nz - 1) * lx * ly + ny * lx + nx] = i;
                        vis[(nz - 1) * lx * ly + ny * lx + nx] = 1;
                        q.push({nx, ny, nz});
                    }
                }
            }
        }
    }
    int x = b.x, y = b.y, z = b.dir;
    while (x >= 0 || y >= 0 || (z >= 1 && z <= 4)) {
        if (x == a.x && y == a.y && z == a.dir)
            break;
        bit2 d = pre[(z - 1) * lx * ly + y * lx + x];
        road.push(d);
        switch (d[0] + d[1] * 2) {
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
    memset(pre, 0, sizeof(bit2) * 4 * N);
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
            for (int k = 0; k < 4; k++) {
                map[k * lx * ly + j * lx + i] = t;
            }
        }
    }

    cin >> start.x >> start.y >> start.dir;
    cin >> mid.x >> mid.y >> mid.dir;
    cin >> endp.x >> endp.y >> endp.dir;
    bfs(mid, endp);
    bfs(start, mid);
    cout << road.size() << endl;
}