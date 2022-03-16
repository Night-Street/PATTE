#include "bits/stdc++.h"

typedef long long ll;
int N, M, c;
//存储在邻接表中的数据结构
struct NextVertex {
    /*
     * v:另一端的顶点
     * w:边权重
     */
    int v;
    int w;
};
//存储在有序集合中的数据结构
struct Edge {
    /*
     * u:顶点1
     * v:顶点2
     * w:边权重
     */
    int u, v, w;
};
namespace std {
    template<>
//    确保所有的边在有序集合中按权重升序排列
    struct less<Edge> {
        bool operator()(const Edge &e1, const Edge &e2) {
            return e1.w < e2.w || e1.w == e2.w && make_pair(e1.u, e1.v) < make_pair(e2.u, e2.v);
        }
    };
}
//kruskal算法需要使用有序集合ks存储所有的边
std::set<Edge, std::less<Edge>> ks;
//使用邻接表存储图，计算D的时候需要使用邻接表。当然本题用邻接矩阵也OK，看个人习惯以及题目具体要求，有些题目用邻接矩阵比较方便。
std::vector<std::vector<NextVertex> > vgraph;
#define inf INT_MAX
/**
 * 计算两个点u,v所在连通块C1,C2的D
 * @param u
 * @param v
 * @return u,v所在连通块C1,C2的D
 */
int D(int u, int v) {
    auto pos = std::find_if(vgraph[u].begin(), vgraph[u].end(), [&](NextVertex &nv) {
        return nv.v == v;
    });
    if (pos == vgraph[u].end())return inf;
    else return pos->w;
}


#define maxn 1005
//并查集数据结构
int father[maxn];
//维护每个点所在连通块的MST中的最大边权及连通块中的点个数。
int mst_maxedge[maxn], cnt[maxn];
/**
 * 计算顶点v所属连通块C的H
 * @param v
 * @return v所属连通块C的H
 */
float H(int v) {
    return mst_maxedge[v] + 1.0 * c / cnt[v];
}
/**
 * 并查集查找算法，查找的同时实现了路径压缩
 * @param n
 * @return
 */
int get_father(int n) {
    return n == father[n] ? n : father[n] = get_father(father[n]);
}
/**
 * 并查集合并算法，会自动将两个点向序号较小的方向合并
 * @param a
 * @param b
 */
void unite(int a, int b) {
    if (get_father(a) == get_father(b))return;
    if (a > b)std::swap(a, b);
    father[get_father(b)] = get_father(a);
}

void init() {

}

void read() {
    std::cin >> N >> M >> c;
    vgraph.resize(N);
    for (int i = 0; i < M; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        vgraph[u].push_back(NextVertex{v, w});
        vgraph[v].push_back(NextVertex{u, w});
        ks.insert(Edge{u, v, w});
    }
//    变量初始化
    for (int i = 0; i < N; ++i) {
        father[i] = i;
        cnt[i] = 1;
        mst_maxedge[i] = 0;
    }
}
/**
 * 可传入多个值的求最大值函数
 * @param num_cnt 要传入的参数个数
 * @param ... 待比较的参数
 * @return 待比较的参数中的最大值
 */
int max(int num_cnt, ...) {
    va_list arg;
    va_start(arg, num_cnt);
    int ans = INT_MIN;
    while (num_cnt--) {
        ans = std::max(ans, va_arg(arg, int));
    }
    va_end(arg);
    return ans;
}

void kruskal() {
    for (Edge e: ks) {
//        限制条件1，两个点属于不同集合再合并
        if (get_father(e.u) == get_father(e.v))continue;
//        限制条件2，两个点
        if (.0 + D(e.u, e.v) > H(e.u) || .0 + D(e.u, e.v) > H(e.v))continue;
        std::unordered_set<int> s1, s2;
//        统计一下属于这两个连通块的所有点并记录下来
        for (int i = 0; i < N; ++i) {
            if (get_father(i) == get_father(e.u))
                s1.insert(i);
            if (get_father(i) == get_father(e.v))
                s2.insert(i);
        }
        unite(e.u, e.v);
//        动态更新mst_maxedge和cnt
        int u_cnt = cnt[e.u], v_cnt = cnt[e.v], max_edge = max(3, mst_maxedge[e.u], mst_maxedge[e.v], e.w);
        for (int x: s1) {
            cnt[x] += v_cnt;
            mst_maxedge[x] = max_edge;
        }
        for (int x: s2) {
            cnt[x] += u_cnt;
            mst_maxedge[x] = max_edge;
        }
    }
}

void solve() {
    kruskal();
    std::map<int, std::set<int> > solutions;
//    将每个集合按其father的值编号，放入solutions中
    for (int i = 0; i < N; ++i) {
        solutions[get_father(i)].insert(i);
    }
//    按照题目要求依次输出每个集合
    for (auto & solution : solutions) {
        bool f = 0;
        for (int x: solution.second) {
            printf("%s%d", f ? " " : "", x);
            f = 1;
        }
        putchar(10);
    }
}

int main() {
    freopen("Depressant.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}