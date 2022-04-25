/*
    Data Structure and Algorithm.
    Created by CLion.
    Author: Depressant
    Date: 2022.3.31
    Time: 上午 10:57
*/
#include "bits/stdc++.h"

#define maxn 25
typedef long long ll;
std::vector<std::vector<int> > vgraph;
int N, M;
int st = 0, ed;
ll cnt = 0;
namespace std {
    template<>
    struct hash<pair<int, int> > {
        size_t operator()(const pair<int, int> &p) const {
            return p.first * maxn + p.second;
        }
    };
}
std::unordered_map<std::string, int> name2id;
std::unordered_map<int, std::string> id2name;

void init() {

}

int store(const std::string &name) {
    if (name2id.find(name) == name2id.end()) {
        int size = name2id.size();
        name2id[name] = size;
        id2name[size] = name;
        return size;
    } else return name2id[name];
}

void read() {
    scanf("%d%d%*[ \n]", &N, &M);
    vgraph.resize(N);
    char s[10];
    scanf("%s%*[ \n]", s);
    st = store(s);
    ed = store("ROM");
    for (int i = 0; i < M; ++i) {
        char s1[10], s2[10];
        scanf("%s%s", s1, s2);
        int v1 = store(s1);
        int v2 = store(s2);
        vgraph[v1].push_back(v2);
        vgraph[v2].push_back(v1);
    }
}

int prv[maxn];
bool reachable[maxn] = {false}, alongside[maxn] = {false};

void trace_back(int cur) {
    while (cur != prv[cur]) {
        alongside[cur] = true;
        cur = prv[cur];
    }
}


void dfs(int cur) {
    static bool vis[maxn] = {false};
    vis[cur] = true;
    reachable[cur] = true;
    if (cur == ed) {
        cnt++;
        trace_back(ed);
    } else {
        for (int nxt: vgraph[cur]) {
            if (vis[nxt])
                continue;
            prv[nxt] = cur;
            dfs(nxt);
        }
    }
    vis[cur] = false;
}

void solve() {
    prv[st] = st;
    dfs(st);
    bool f = true;
    for (int i = 0; i < N; ++i) {
        if (i == st)continue;
        if (reachable[i] && !alongside[i])
            f = false;
    }
    puts(f ? "Yes" : "No");
    std::cout << cnt;
}

int main() {
//    freopen("Depressant.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}