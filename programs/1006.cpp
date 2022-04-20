#include "bits/stdc++.h"

#define maxn 105
typedef long long ll;
int N;
int pre_seq[maxn], in_seq[maxn], post_seq[maxn];

bool table[maxn] = {false};
int root = 0;
int lchild[maxn] = {0}, rchild[maxn] = {0};

void init() {

}

void read_seq(int *seq) {
    char num[10];
    for (int i = 0; i < N; ++i) {
        scanf("%s%*[ \n]", num);
        try {
            seq[i] = std::stoi(num);
            table[seq[i]] = true;
        } catch (std::invalid_argument &argument) {
            seq[i] = 0;
        }
    }
}

int mmax(int cnt, ...) {
    va_list ap;
    va_start(ap, cnt);
    int ret = INT_MIN;
    while (cnt--) {
        int tmp = va_arg(ap, int);
        ret = std::max(ret, tmp);
    }
    return ret;
}

void read() {
    std::cin >> N;
    getchar();
    read_seq(in_seq);
    read_seq(pre_seq);
    read_seq(post_seq);
}

void pre_order(int cur) {
    if (!cur)return;
    static bool f = 0;
    printf("%s%d", f ? " " : "", cur);
    f = 1;
    pre_order(lchild[cur]);
    pre_order(rchild[cur]);
}

void in_order(int cur) {
    if (!cur)return;
    static bool f = 0;
    in_order(lchild[cur]);
    printf("%s%d", f ? " " : "", cur);
    f = 1;
    in_order(rchild[cur]);
}

void post_order(int cur) {
    if (!cur)return;
    static bool f = 0;
    post_order(lchild[cur]);
    post_order(rchild[cur]);
    printf("%s%d", f ? " " : "", cur);
    f = 1;
}

void level_order(int cur) {
    if (!cur)return;
    std::queue<int> q;
    q.push(cur);
    bool f = 0;
    while (!q.empty()) {
        auto F = q.front();
        q.pop();
        printf("%s%d", f ? " " : "", F);
        f = 1;
        if (lchild[F])q.push(lchild[F]);
        if (rchild[F])q.push(rchild[F]);
    }
}

bool dfs(int &cur_node, int inL, int inR, int preL, int preR, int postL, int postR) {
    if (inL > inR) {
        cur_node = 0;
        return true;
    }
//    枚举中序序列的每个点
    for (int i = inL; i <= inR; ++i) {
//        判断此点是否具有成为子树树根的必要条件
        if (in_seq[i] && pre_seq[preL] && in_seq[i] != pre_seq[preL])continue;
        if (in_seq[i] && post_seq[postR] && in_seq[i] != post_seq[postR])continue;
        if (pre_seq[preL] && post_seq[postR] && pre_seq[preL] != post_seq[postR])continue;
//        有可能有些序列恰好缺失此节点的值，因此取此节点在三个序列中的最大值
        cur_node = mmax(3, in_seq[i], pre_seq[preL], post_seq[postR]);
//        如果三个序列都没有给出此节点的值，则此点只可能是唯一一个没有出现过的值
        if (cur_node == 0)
            cur_node = std::min_element(table + 1, table + N + 1) - table;
//        递归构造左右子树
        int l_size = i - inL;
        if (!dfs(lchild[cur_node], inL, i - 1, preL + 1, preL + l_size, postL, postL + l_size - 1))continue;
        if (!dfs(rchild[cur_node], i + 1, inR, preL + l_size + 1, preR, postL + l_size, postR - 1))continue;
        return true;
    }
    return false;
}

bool judge() {
//    缺失值个数超过1，则必然无法确定唯一的二叉树
    if (std::count_if(table + 1, table + 1 + N, [](bool f) {
        return !f;
    }) > 1)
        return false;
    return dfs(root, 0, N - 1, 0, N - 1, 0, N - 1);
}

void solve() {
    if (!judge())puts("Impossible");
    else {
        in_order(root);
        putchar(10);
        pre_order(root);
        putchar(10);
        post_order(root);
        putchar(10);
        level_order(root);
    }
}

int main() {
//    freopen("Depressant.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}