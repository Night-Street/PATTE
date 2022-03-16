#include <bits/stdc++.h>

#define maxn 5005
using namespace std;
string src, dst;
unordered_map<string, int> name2id;
unordered_map<int, string> id2name;
int N, idx = 1, M;
int ResNet[maxn][maxn] = {0};
int prv[maxn] = {0};

bool bfs(int src, int dst) {
    bool vis[maxn] = {0};
    memset(prv, 0, sizeof prv);
    queue<int> q;
    q.push(src);
    vis[src] = 1;
    while (!q.empty()) {
        auto F = q.front();
        q.pop();
        for (int i = 1; i <= N; ++i) {
            if (ResNet[F][i] && !vis[i]) {
                q.push(i);
                vis[i] = 1;
                prv[i] = F;
                if (i == dst)return 1;
            }
        }
    }
    return 0;
}

int update(int st, int ed) {
    int min_val = INT_MAX;
    int cur = ed;
    while (cur != st) {
        min_val = min(min_val, ResNet[prv[cur]][cur]);
        cur = prv[cur];
    }
    cur = ed;
    while (cur != st) {
        ResNet[prv[cur]][cur] -= min_val;
        cur = prv[cur];
    }
    return min_val;
}

void solve() {
    int st = name2id[src], ed = name2id[dst], ans = 0;
    N = name2id.size();
    while (1) {
        if (bfs(st, ed)) {
            ans += update(st, ed);
        } else {
            break;
        }
    }
    cout << ans;
}

int main() {
//    freopen("case.txt", "r", stdin);
    cin >> src >> dst >> M;
    for (int i = 0; i < M; ++i) {
        string st, ed;
        int cap;
        cin >> st >> ed >> cap;
        if (name2id.find(st) == name2id.end()) {
            name2id[st] = idx;
            id2name[idx] = st;
            idx++;
        }
        if (name2id.find(ed) == name2id.end()) {
            name2id[ed] = idx;
            id2name[idx] = ed;
            idx++;
        }
        ResNet[name2id[st]][name2id[ed]] = cap;
    }
    solve();
    return 0;
}