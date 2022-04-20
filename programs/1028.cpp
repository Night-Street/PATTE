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
//            int x = std::min(p.first, p.second), y = std::max(p.first, p.second);
//            return x * maxn + y;
        }
    };

//    template<>
//    struct equal_to<pair<int, int> > {
//        bool operator()(const pair<int, int> &p1, const pair<int, int> &p2) const {
//            return hash<pair<int, int> >()(p1) == hash<pair<int, int> >()(p2);
//        }
//    };
}
std::unordered_map<std::string, int> name2id;
std::unordered_map<int, std::string> id2name;
//std::unordered_set<std::pair<int, int> > edges;

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
//        edges.insert(std::make_pair(std::min(v1, v2), std::max(v1, v2)));
//        edges.insert(std::make_pair(v1, v2));
    }
//    ed = name2id["ROM"];
}


int prv[maxn] = {0};
bool check_in[maxn] = {false};

void trace_back(int cur) {
    if (cur == prv[cur])
        return;
//    edges.erase(std::make_pair(std::min(cur, prv[cur]), std::max(cur, prv[cur])));
//    edges.insert(std::make_pair(cur, prv[cur]));
//    check_in[cur] = true;
    trace_back(prv[cur]);
}

bool f = true;

void dfs(int cur) {
    static bool vis[maxn] = {false};
    vis[cur] = true;
    check_in[cur] = true;
    if (cur == ed) {
        cnt++;
        trace_back(cur);
    } else {
        bool flag = false;
        for (int nxt: vgraph[cur]) {
            if (vis[nxt])
                continue;
            prv[nxt] = cur;
            dfs(nxt);
            flag = true;
        }
        if (!flag)
            f = false;
    }
    vis[cur] = false;
}

void solve() {
    prv[st] = st;
//    check_in[st] = true;
    dfs(st);
//    if (!edges.empty())
//    if (!*std::min_element(check_in, check_in + N))
    if (!*std::min_element(check_in, check_in + N) || !f)
        puts("No");
    else
        puts("Yes");
    std::cout << cnt;
}

int main() {
    freopen("Depressant.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}