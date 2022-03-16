#include "bits/stdc++.h"

using namespace std;
int N, M, K;
#define maxn 10005
vector<vector<int>> v_graph;
int father[maxn];

int get_father(int n) {
    if (n == father[n])return n;
    else return father[n] = get_father(father[n]);
}

void unite(int a, int b) {
    int fa = get_father(a), fb = get_father(b);
    if (fa != fb) {
        father[fb] = fa;
    }
}


void dfs(int cur) {
    static int tdx = 0;
    static int dfn[maxn] = {0};
    static int low[maxn] = {0};
    static bool in_stack[maxn] = {false};
    static stack<int> stk;

    dfn[cur] = low[cur] = ++tdx;
    stk.push(cur);
    in_stack[cur] = true;

    for (int nxt: v_graph[cur]) {
        if (!in_stack[nxt] && dfn[nxt] == 0) {
            dfs(nxt);
            low[cur] = min(low[cur], low[nxt]);
        } else if (in_stack[nxt] && dfn[nxt] != 0) {
            low[cur] = min(low[cur], dfn[nxt]);
        }
    }

    if (dfn[cur] == low[cur]) {
        while (1) {
            auto T = stk.top();
            stk.pop();
            in_stack[T] = 0;
            unite(cur, T);
            if (T == cur)break;
        }
    }
}

int main() {
//    freopen("in.txt", "r", stdin);
    cin >> N >> M;
    father[0] = 0;
    v_graph.resize(N + 1);
    for (int i = 1; i <= N; ++i) {
        father[i] = i;
        v_graph[0].push_back(i);
    }
    for (int i = 0; i < M; i++) {
        int st, ed;
        scanf("%d%d", &st, &ed);
        v_graph[st].push_back(ed);
    }
    dfs(1);
    cin >> K;
//    for (int i = 0; i < N; ++i) {
//        if (vis[i + 1])continue;
//        dfs(i + 1);
//    }
    for (int i = 0; i < K; ++i) {
        int v1, v2;
        scanf("%d%d", &v1, &v2);
        if (get_father(v1) == get_father(v2)) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
    return 0;
}