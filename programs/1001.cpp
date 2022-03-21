#include "bits/stdc++.h"

#define maxn 505
using namespace std;
int N, M;
struct NextVertex {
    int ed;
    int cost;
    int status;
};

struct Edge {
    int v1, v2, cost, status;
};


vector<vector<NextVertex> > v_graph;


int father[maxn];

int getFtr(int n) {
    if (father[n] == n)return n;
    else return father[n] = getFtr(father[n]);
}

void unite(int a, int b) {
    int fa = getFtr(a);
    int fb = getFtr(b);
    if (fa != fb) {
        father[fb] = fa;
    }
}
//存储图中的边
vector<Edge> edges;
//存储割点
set<int> cut;

/**
 * 通过dfs树求图中的割点
 * @param cur dfs树遍历过程中的当前节点
 * @param father 顶点cur在dfs树上的父节点
 * @param root dfs树的根节点
 * @return
 */
void dfs(int cur, int father, int root) {
    static int dfn[maxn];
    static int tdx = 0;
    static int low[maxn];
    int child_cnt = 0;
    dfn[cur] = low[cur] = ++tdx;
    for (NextVertex nxt_v: v_graph[cur]) {
        int nxt = nxt_v.ed;
        if (!dfn[nxt]) {
            child_cnt++;
            dfs(nxt, cur, root);
            low[cur] = min(low[cur], low[nxt]);
            if (dfn[cur] <= low[nxt] && cur != root) {
                cut.insert(cur);
            } else if (cur == root && child_cnt > 1) {
                cut.insert(cur);
            }
        } else {
            if (nxt != father) {
                low[cur] = min(low[cur], dfn[nxt]);
            }
        }
    }
}
/**
 * 通过kruskal算法构建最小生成树，并求出修路所需费用
 * @param except 被占领的城市，计算最小生成树时跳过与此点相连的边
 * @return 修路所需费用
 */
int MST(int except) {
    int ckpt[maxn];
    for (int i = 1; i <= N; i++) {
        ckpt[i] = father[i];
        father[i] = i;
    }

    int ans = 0;
    for (Edge e: edges) {
        if (e.v1 != except && e.v2 != except) {
            if (getFtr(e.v1) != getFtr(e.v2))
                if (e.status == 0) {
                    ans += e.cost;
                }
            unite(e.v1, e.v2);
        }
    }
    for (int i = 1; i <= N; i++) {
        father[i] = ckpt[i];
    }

    return ans;
}

int main() {
    cin >> N >> M;

    v_graph.resize(N + 1);
    for (int i = 0; i < N; i++) {
        father[i + 1] = i + 1;
    }

    for (int i = 0; i < M; i++) {
        int c1, c2, cost, status;
        scanf("%d%d%d%d", &c1, &c2, &cost, &status);
        v_graph[c1].push_back(NextVertex{c2, cost, status});
        v_graph[c2].push_back(NextVertex{c1, cost, status});
        edges.push_back(Edge{c1, c2, cost, status});
        if (status == 1) {
            unite(c1, c2);
        }
    }
    sort(edges.begin(), edges.end(), [&](Edge a, Edge b) {
        return a.status > b.status || a.status == b.status && a.cost < b.cost;
    });
//    先求出图中的割点
    dfs(1, 1, 1);
    if (cut.size()) {
//        如果存在割点，直接输出所有割点
        bool f = 0;
        for (int cut_v: cut) {
            printf("%s%d", f ? " " : "", cut_v);
            f = 1;
        }
    } else {
        int max_cost = -1;
//        存储最应受到关注城市的顶点编号
        vector<int> v_set;
        for (int i = 1; i <= N; i++) {
//            遍历图中每个点，构建一棵最小生成树，计算出修路所需费用。记录下费用最多的点。
            int cost = MST(i);
            if (cost == 0)continue;
            if (cost > max_cost) {
                max_cost = cost;
                v_set.clear();
                v_set.push_back(i);
            } else if (max_cost == cost) {
                v_set.push_back(i);
            }
        }
//        按照题目要求，如果没有任何一座城市被占领后需要花钱修路，则输出0
        if (v_set.size() == 0) {
            cout << "0";
        } else {
//            升序输出
            sort(v_set.begin(), v_set.end());
            bool f = 0;
            for (int x: v_set) {
                printf("%s%d", f ? " " : "", x);
                f = 1;
            }
        }
    }
    return 0;
}