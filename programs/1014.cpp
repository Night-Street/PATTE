#include "bits/stdc++.h"
//隐藏条件：一个人单独成团，他跟自己的距离也是0
#define maxn 1005
int N, k;
typedef long long ll;
std::vector<std::vector<int> > vgraph;
int father[maxn];
std::unordered_set<int> circle_idx;

int get_father(int n) {
    return father[n] == n ? n : (father[n] = get_father(father[n]));
}

void unite(int a, int b) {
    if (get_father(a) != get_father(b)) {
        father[get_father(b)] = get_father(a);
    }
}

void init() {

}

void read() {
    std::cin >> N;
    vgraph.resize(N + 1);
    for (int i = 0; i < N; ++i) {
        int cur = i + 1;
        father[cur] = cur;
    }

    for (int i = 0; i < N; ++i) {
        int cur = i + 1;
        scanf("%d", &k);
        for (int j = 0; j < k; ++j) {
            int x;
            scanf("%d", &x);
            vgraph[cur].push_back(x);
            vgraph[x].push_back(cur);
            unite(cur, x);
        }
    }

}

std::vector<int> ret;

int bfs(int cur) {
    ret.clear();
    std::queue<int> q;
    std::vector<int> tmp;
    bool vis[maxn] = {0};
    q.push(cur);
    tmp.push_back(cur);
    vis[cur] = 1;

    int lvl = 0, tot = 1, cnt = 0;
    while (!q.empty()) {
        auto F = q.front();
        tmp.push_back(F);
        q.pop();
        for (int nxtv: vgraph[F]) {
            if (!vis[nxtv]) {
                vis[nxtv] = 1;
                q.push(nxtv);
            }
        }
        cnt++;
        if (cnt == tot) {
            lvl++;
            ret.assign(tmp.begin(), tmp.end());
            tot = q.size();
            cnt = 0;
        }
    }
    return lvl - 2;
}

void solve() {
    for (int i = 0; i < N; ++i) {
        int cur = i + 1;
        get_father(cur);
    }
    for (int i = 0; i < N; ++i) {
        int cur = i + 1;
        circle_idx.insert(father[cur]);
    }
    std::cout << circle_idx.size();
    int d = -1;
    for (int x: circle_idx) {
        bfs(x);
        for (int y: ret) {
            d = std::max(d, bfs(y));
        }
    }
    std::cout << " " << std::max(0, d);
}

int main() {
//    freopen("case.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}