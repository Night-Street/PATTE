#include "bits/stdc++.h"

using namespace std;
#define maxn 305
int N, n;
double dp[maxn][maxn][15] = {0.0};
int prv[maxn][maxn][15];
int st = -1, ed = -1, ans = -1;

struct Point2D {
    int id;
    double posx;
    double posy;

    Point2D(int id, double x, double y) {
        this->id = id;
        this->posx = x;
        this->posy = y;
    }
};

vector<Point2D *> i2p;
Point2D center_point(-1, 0, 0);
vector<int> ans_list;

double get_angle(const Point2D &p1, const Point2D &p2) {
    return atan2(p2.posy - p1.posy, p2.posx - p1.posx);
}

double area(const Point2D &p1, const Point2D &p2, const Point2D &p3) {
    return fabs((p3.posx - p1.posx) * (p2.posy - p1.posy) - (p3.posy - p1.posy) * (p2.posx - p1.posx));
}

double area(int a, int b, int c) {
    return area(*i2p[a], *i2p[b], *i2p[c]);
}

void trace_back(int top, int k) {
    ans_list.push_back(i2p[top]->id);
    if (k == 2) {
        ans_list.push_back(i2p[st]->id);
        return;
    }
    trace_back(prv[st][top][k], k - 1);
}

void solve() {
    center_point.posx /= N, center_point.posy /= N;
    sort(i2p.begin(), i2p.end(), [&](Point2D *p1, Point2D *p2) {
        return get_angle(center_point, *p1) < get_angle(center_point, *p2);
    });
//    for (auto p:i2p) {
//        cout<<p->id<<endl;
//    }
    for (int k = 3; k <= n; ++k) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; ++j) {
                for (int l = i + 1; l < j; ++l) {
                    if (dp[i][j][k] <= dp[i][l][k - 1] + area(i, l, j)) {
                        dp[i][j][k] = dp[i][l][k - 1] + area(i, l, j);
                        prv[i][j][k] = l;
                    }
                }
            }
        }
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (dp[i][j][n] > ans) {
                st = i, ed = j, ans = dp[i][j][n];
            }
        }
    }
//    printf("%d %d %d\n", i2p[ed]->id, i2p[ed]->id, ans);
    trace_back(ed, n);
    sort(ans_list.begin(), ans_list.end());
    bool f = 0;
    for (auto it = ans_list.rbegin(); it != ans_list.rend(); it++) {
        printf("%s%d", f ? " " : "", *it);
        f = 1;
    }
}

int main() {
//    freopen("case.txt", "r", stdin);
    cin >> N >> n;
    for (int i = 0; i < N; ++i) {
        double x, y;
        scanf("%lf%lf", &x, &y);
        i2p.push_back(new Point2D(i, x, y));
        center_point.posx += x;
        center_point.posy += y;
    }
    solve();
    return 0;
}