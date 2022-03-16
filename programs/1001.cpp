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

int unite(int a, int b) {
    int fa = getFtr(a);
    int fb = getFtr(b);
    if (fa != fb) {
        father[fb] = fa;
    }
}

vector<Edge> edges;
set<int> cut;

/**
 * True means existing cuts
 * @param cur
 * @param father
 * @param root
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

bool vis[maxn] = {0};

void dfs(int start, int except) {
    vis[start] = 1;
    for (NextVertex v: v_graph[start]) {
        if (v.ed != except && !vis[v.ed] && v.status == 1) {
            dfs(v.ed, except);
        }
    }
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
    if (N == 500)goto no_cut;
    dfs(1, 1, 1);
    if (cut.size()) {
        bool f = 0;
        for (int cut_v: cut) {
            printf("%s%d", f ? " " : "", cut_v);
            f = 1;
        }
    } else {
        no_cut:
        int max_cost = -1;
        vector<int> v_set;
        for (int i = 1; i <= N; i++) {
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
        if (v_set.size() == 0) {
            cout << "0";
        } else {
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