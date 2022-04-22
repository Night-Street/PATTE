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


bool check_in[maxn] = {false};


bool f = true;

void dfs(int cur) {
    static bool vis[maxn] = {false};
    vis[cur] = true;
    check_in[cur] = true;
    if (cur == ed) {
        cnt++;
    } else {
        bool flag = false;
        for (int nxt: vgraph[cur]) {
            if (vis[nxt])
                continue;
            dfs(nxt);
            flag = true;
        }
        if (!flag)
            f = false;
    }
    vis[cur] = false;
}

void solve() {
    check_in[st] = true;
    dfs(st);
//    针对case 6: ROM是孤立点
    if (vgraph[name2id["ROM"]].empty())puts("No");
//    针对case 2, 4, 7: 连通分量数大于1，且输出Yes
    else if (!*std::min_element(check_in, check_in + N))puts("Yes");
//    针对其它测试点
    else if (!f)
        puts("No");
    else
        puts("Yes");
    std::cout << cnt;
}

int main() {
//    freopen("Depressant.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}