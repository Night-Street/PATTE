#include "bits/stdc++.h"

#define maxn 105
typedef long long ll;
int N;
int pre_seq[maxn], in_seq[maxn], post_seq[maxn];

struct Node {
    int v;
    Node *l, *r;

    explicit Node(int v) : v(v) { l = r = nullptr; }

    Node(int v, Node *l, Node *r) : v(v), l(l), r(r) {}
};

Node *root = nullptr;

void init() {

}

void read_seq(int *seq) {
    char num[10];
    for (int i = 0; i < N; ++i) {
        scanf("%s", num);
        getchar();
        if (num[0] != '-')seq[i] = atoi(num);
    }
}

void read() {
    std::cin >> N;
    read_seq(in_seq);
    read_seq(pre_seq);
    read_seq(post_seq);
}

void pre_order(Node *cur) {
    if (!cur)return;
    static bool f = 0;
    printf("%s%d", f ? " " : "", cur->v);
    f = 1;
    pre_order(cur->l);
    pre_order(cur->r);
}

void in_order(Node *cur) {
    if (!cur)return;
    static bool f = 0;
    in_order(cur->l);
    printf("%s%d", f ? " " : "", cur->v);
    f = 1;
    in_order(cur->r);
}

void post_order(Node *cur) {
    if (!cur)return;
    static bool f = 0;
    post_order(cur->l);
    post_order(cur->r);
    printf("%s%d", f ? " " : "", cur->v);
    f = 1;
}

void level_order(Node *cur) {
    std::queue<Node *> q;
    q.push(cur);
    bool f = 0;
    while (!q.empty()) {
        auto F = q.front();
        q.pop();
        printf("%s%d", f ? " " : "", cur->v);
        f = 1;
        if (cur->l)q.push(cur->l);
        if (cur->r)q.push(cur->r);
    }
}

bool dfs(Node *&cur, int inL, int inR, int preL, int preR, int postL, int postR) {
    if (inL > inR) {
        cur = 0;
        return true;
    }
    if (pre_seq[preL] && post_seq[postR] && pre_seq[preL] != post_seq[postR])return false;
    for (int i = inL; i <= inR; ++i) {
        if (in_seq[i] && pre_seq[preL] && in_seq[i] != pre_seq[preL])continue;
        if (in_seq[i] && post_seq[postR] && in_seq[i] != post_seq[postR])continue;
        cur = new Node(in_seq[i]);
        int left_size = i - inL;
        if (!dfs(cur->l, inL, i - 1, preL + 1, preL + left_size, postL, postL + left_size - 1))continue;
        if (!dfs(cur->r, i + 1, inR, preL + left_size + 1, preR, postL + left_size, postR - 1))continue;
        return true;
    }
    return false;
}

bool judge() {
    return dfs(root, 0, N - 1, 0, N - 1, 0, N - 1);

}

void solve() {
    if (!judge())puts("Impossible");
    else {
        in_order(root);
        puts("");
        pre_order(root);
        puts("");
        post_order(root);
        puts("");
        level_order(root);
    }
}

int main() {
    freopen("case.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}