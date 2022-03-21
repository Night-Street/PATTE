/*
    Data Structure and Algorithm.
    Created by CLion.
    Author: Depressant
    Date: 2022.3.16
    Time: 下午 5:12
*/
#include "bits/stdc++.h"

int N, M, L;
typedef long long ll;
#define maxn 105
bool werewolf[maxn];
bool liar[maxn];
int words[maxn];

void init() {

}

void read() {
    std::cin >> N >> M >> L;
    for (int i = 1; i <= N; ++i) {
        scanf("%d", &words[i]);
    }
}

bool judge() {
    if()
    return true;
}

void output_werewolves() {
    bool f = false;
    for (int i = N; i >= 1; --i) {
        if (werewolf[i]) {
            printf("%s%d", f ? " " : "", i);
            f = true;
        }
    }
    putchar(10);
}
void output_liars() {
    bool f = false;
    for (int i = N; i >= 1; --i) {
        if (liar[i]) {
            printf("%s%d", f ? " " : "", i);
            f = true;
        }
    }
    putchar(10);
}

void dfs_M(int cur_cnt, int pos) {
    werewolf[pos] = true;
    cur_cnt++;
    if (cur_cnt == M && judge()) {
        output_werewolves();
    } else {
        for (int i = pos - 1; i >= 1; --i) {
            dfs_M(cur_cnt, i);
        }
    }
    cur_cnt--;
    werewolf[pos] = false;
}
void dfs_L(int cur_cnt, int pos) {
    liar[pos] = true;
    cur_cnt++;
    if (cur_cnt == L && judge()) {
        output_liars();
    } else {
        for (int i = pos - 1; i >= 1; --i) {
            dfs_L(cur_cnt, i);
        }
    }
    cur_cnt--;
    liar[pos] = false;
}
void solve() {
    for (int i = N; i >= L - 1; --i) {
        dfs_M(0, i);
    }
    for (int i = N; i >= L - 1; --i) {
        dfs_L(0, i);
    }
}

int main() {
    freopen("Depressant.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}