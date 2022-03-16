#include "bits/stdc++.h"

using namespace std;
#define maxn 1005
int N;
int tot = 0;
unordered_map<char, int> counter;
string string_set[maxn];
int ans = INT_MAX;

class Func {
public:
    void operator()(char c) {

    }
};

template<typename Func>
void read_string(Func func) {
    char c;
    do {
        c = (char) getchar();
        if (c != 10) {
            func(c);
        }
    } while (c != '\n');
}

//void select(int pos) {
//    for (char c: string_set[pos]) {
//        counter[c]--;
//    }
//}
//
//void deselect(int pos) {
//    for (char c: string_set[pos])counter[c]++;
//
//}
//
//void dfs(int pos, int cnt) {
//    if (pos == N)return;
//    int rem = 0;
//    for_each(counter.begin(), counter.end(), [&](pair<char, int> p) {
//        if (p.second < 0)rem -= p.second;
//    });
//    if (rem >= ans)return;
//
//    select(pos);
//    cnt += (int) string_set[pos].length();
//    if (all_of(counter.begin(), counter.end(), [](pair<char, int> p) {
//        return p.second <= 0;
//    })) {
//        ans = min(ans, cnt - tot);
//    } else {
//        dfs(pos + 1, cnt);
//    }
//    deselect(pos);
//    cnt -= (int) string_set[pos].length();
//    dfs(pos + 1, cnt);
//}

struct Node {

    int pos;
    int cnt;
    unordered_map<char, int> counter;

    Node(int pos, int cnt, const unordered_map<char, int> &counter) : pos(pos), cnt(cnt), counter(counter) {}

    explicit Node(Node *node) {
        this->pos = node->pos;
        this->cnt = node->cnt;
        this->counter = node->counter;
    }
};

void select(int pos, unordered_map<char, int> &cur_counter) {
    for (char c: string_set[pos])cur_counter[c]--;
}

queue<Node *> q;

void bfs() {
    q.push(new Node{0, 0, counter});
    while (!q.empty()) {
        auto F = q.front();
        q.pop();
        if (F->pos == N)continue;
        int rem = 0;
        for_each(F->counter.begin(), F->counter.end(), [&](pair<char, int> p) {
            if (p.second < 0)rem -= p.second;
        });
        if (rem >= ans)continue;

        Node *select_node = new Node(F);
        select(select_node->pos, select_node->counter);
        select_node->cnt += (int) string_set[select_node->pos].length();
        select_node->pos++;
        if (all_of(select_node->counter.begin(), select_node->counter.end(), [&](pair<char, int> p) {
            return p.second <= 0;
        })) {
            ans = min(ans, select_node->cnt - tot);
        } else {
            q.push(select_node);
        }

        Node *deselect_node = new Node(F);
        deselect_node->pos++;
        q.push(deselect_node);

        delete (F);
    }
}

void solve() {
//    dfs(0, 0);
    bfs();
    printf("Yes %d", ans);
}


int main() {
    freopen("case.txt", "r", stdin);
    read_string([&](char c) {
        counter[c]++;
        tot++;
    });
    auto ckpt = counter;
    cin >> N;
    getchar();
    for (int i = 0; i < N; ++i) {
        string cur;
        read_string([&](char c) {
            cur.push_back(c);
            if (counter[c] > 0)counter[c]--;
            if (counter[c] == 0)counter.erase(c);
        });
        string_set[i] = cur;
    }
    if (!counter.empty()) {
        ans = 0;
        for (auto p: counter) {
            ans += p.second;
        }
        printf("No %d", ans);
    } else {
        counter = ckpt;
        solve();
    }
    return 0;
}