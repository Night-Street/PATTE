#include "bits/stdc++.h"

using namespace std;
int N;
int delta = 15;

struct Point2D {
    int x;
    int y;

    Point2D(int x, int y) {
        this->x = x;
        this->y = y;
    }

    static double calc_edge(const Point2D &p1, const Point2D &p2) {
        return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
    }
};

typedef vector<Point2D> Polygon;
Polygon pl1, pl2;
vector<double> angles1, angles2;
vector<double> edges1, edges2;

void read_polygon(vector<Point2D> &v) {
    v.clear();
    int K;
    scanf("%d", &K);
    for (int i = 0; i < K; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        v.push_back(Point2D(x, y));
    }
}

vector<double> calc_edges(Polygon &polygon) {
    vector<double> ret;
    for (int i = 0; i < polygon.size() - 1; ++i) {
        double edge = Point2D::calc_edge(polygon[i], polygon[i + 1]);
        ret.push_back(edge);
    }
    ret.push_back(Point2D::calc_edge(*polygon.rbegin(), *polygon.begin()));
    return ret;
}

double round(double v, int d) {
    v *= pow(10, d);
    v = round(v);
    v /= pow(10, d);
    return v;
}

double calc_angle(Point2D &p1, Point2D &p2, Point2D &p3) {
    double a = Point2D::calc_edge(p1, p2), b = Point2D::calc_edge(p2, p3), c = Point2D::calc_edge(p3, p1);
    double v = (a * a + b * b - c * c) / (2 * a * b);
    return round(acos(v), delta);
}

vector<double> calc_angles(Polygon &p) {
    vector<double> ret;
//    ret.reserve(p.size());
    for (int i = 0; i < p.size(); ++i) {
        ret.push_back(calc_angle(p[(i - 1 + p.size()) % p.size()], p[i], p[(i + 1) % p.size()]));
    }
    return ret;
}

bool judge() {
//    确保第一个多边形的边数不多于第二个多边形
    if (pl1.size() > pl2.size())
        swap(pl1, pl2);
    if (!(pl1.size() == 3 && pl2.size() == 3 || pl1.size() == 3 && pl2.size() == 4 ||
          pl1.size() == 4 && pl2.size() == 4 || pl1.size() == 3 && pl2.size() == 5))
        return false;
    angles1 = calc_angles(pl1);
    edges1 = calc_edges(pl1);
    angles2 = calc_angles(pl2);
    edges2 = calc_edges(pl2);
    if (pl1.size() == 3 && pl2.size() == 3) {
//    两个直角三角形
        int idx1 = std::find(angles1.begin(), angles1.end(), round(M_PI_2, delta)) - angles1.begin();
        int idx2 = std::find(angles2.begin(), angles2.end(), round(M_PI_2, delta)) - angles2.begin();
        if (idx1 == 3 || idx2 == 3)return false;
//      当且仅当斜边相等，才能拼成一个矩形
        return edges1[(idx1 + 1) % pl1.size()] == edges2[(idx2 + 1) % pl2.size()];
    } else if (pl1.size() == 3 && pl2.size() == 4) {
//        直角三角形与直角梯形
        int tmp = std::find(angles1.begin(), angles1.end(), round(M_PI_2, delta)) - angles1.begin();
        if (tmp == 3)
            return false;
        int idx = -1;
        for (int i = 0; i < angles2.size(); ++i) {
            if (angles2[i] == round(M_PI_2, delta)) {
                if (angles2[(i + 1) % angles2.size()] == round(M_PI_2, delta)) {
                    idx = i;
                    break;
                } else if (angles2[(i - 1 + angles2.size()) % angles2.size()] == round(M_PI_2, delta)) {
                    idx = (i - 1 + angles2.size()) % angles2.size();
                    break;
                }
            }
        }
        if (idx == -1)
            return false;
//        确保直角三角形斜边与直角梯形的非直角邻边相等
        return edges2[(idx + 2) % edges2.size()] == edges1[(tmp + 1) % edges1.size()];
    } else if (pl1.size() == 4 && pl2.size() == 4) {
//        两个四边形
        if (std::count(angles1.begin(), angles1.end(), round(M_PI_2, delta)) == 4 &&
            std::count(angles2.begin(), angles2.end(), round(M_PI_2, delta)) == 4) {
//          两个矩形
//          当且仅当其中一个矩形的某条边与另一矩形的某条边相等，才能拼成一个矩形
            bool fail = true;
            for (double edge: edges1) {
                if (std::find(edges1.begin(), edges1.end(), edge) != edges1.end()) {
                    fail = false;
                    break;
                }
            }
            return !fail;
        } else if (std::count(angles1.begin(), angles1.end(), round(M_PI_2, delta)) == 2 &&
                   std::count(angles2.begin(), angles2.end(), round(M_PI_2, delta)) == 2) {
//            两个直角梯形，确保两个直角梯形的非直角邻边相等，且直角腰也相等
            int i1 = -1;
            for (int i = 0; i < angles1.size(); ++i) {
                if (angles1[i] == round(M_PI_2, delta)) {
                    if (angles1[(i + 1) % angles1.size()] == round(M_PI_2, delta)) {
                        i1 = i;
                        break;
                    } else if (angles1[(i - 1 + angles1.size()) % angles1.size()] == round(M_PI_2, delta)) {
                        i1 = (i - 1 + angles1.size()) % angles1.size();
                        break;
                    }
                }
            }
            if (i1 == -1)
                return false;
            int i2 = -1;
            for (int i = 0; i < angles2.size(); ++i) {
                if (angles2[i] == round(M_PI_2, delta)) {
                    if (angles2[(i + 1) % angles2.size()] == round(M_PI_2, delta)) {
                        i2 = i;
                        break;
                    } else if (angles2[(i - 1 + angles2.size()) % angles2.size()] == round(M_PI_2, delta)) {
                        i2 = (i - 1 + angles2.size()) % angles2.size();
                        break;
                    }
                }
            }
            if (i2 == -1)
                return false;
            return edges1[(i1 + 2) % 4] == edges2[(i2 + 2) % 4] && edges1[i1] == edges2[i2];
        }
    } else if (pl1.size() == 3 && pl2.size() == 5) {
        int tmp = std::find(angles1.begin(), angles1.end(), round(M_PI_2, delta)) - angles1.begin();
        if (tmp == 3)
            return false;
        int idx = -1;
        for (int i = 0; i < angles2.size(); ++i) {
            if (angles2[i] == round(M_PI_2, delta)) {
                if (angles2[(i + 1) % angles2.size()] == round(M_PI_2, delta) &&
                    angles2[(i + 2) % angles2.size()] == round(M_PI_2, delta)) {
                    idx = (i + 1) % angles2.size();
                    break;
                } else if (angles2[(i - 1 + angles2.size()) % angles2.size()] == round(M_PI_2, delta) &&
                           angles2[(i + 1) % angles2.size()] == round(M_PI_2, delta)) {
                    idx = i;
                    break;
                } else if (angles2[(i - 1 + angles2.size()) % angles2.size()] == round(M_PI_2, delta) &&
                           angles2[(i - 2 + angles2.size()) % angles2.size()] == round(M_PI_2, delta)) {
                    idx = (i - 1 + angles2.size()) % angles2.size();
                    break;
                }
            }
        }
        if (idx == -1)
            return false;
        return edges2[(idx + 2) % angles2.size()] == edges1[(tmp + 1) % edges1.size()];
    }
    return false;
}

void solve() {
    read_polygon(pl1);
    read_polygon(pl2);
    bool f = 0;
    if (pl1.size() == 4 && pl2.size() == 4) {
        f = 1;
        delta = 14;
    }
    if (judge())puts("YES");
    else puts("NO");
    if (f)
        delta = 15;
}

int main() {
//    freopen("case.txt", "r", stdin);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        solve();
    }
    return 0;
}