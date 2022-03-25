/*
    Data Structure and Algorithm.
    Created by CLion.
    Author: Depressant
    Date: 2022.3.21
    Time: 下午 9:50
*/
#include "bits/stdc++.h"

typedef long long ll;
#define maxn 105
int N, M, L;
int statements[maxn];
bool is_wolf[maxn];

void init() {

}

void read() {
    std::cin >> N >> M >> L;
    for (int i = 0; i < N; ++i) {
        int x;
        scanf("%d", &x);
        statements[i + 1] = x;
    }
}

void output_wolves() {
    bool f = false;
    for (int i = N; i > 0; --i) {
        if (!is_wolf[i])continue;
        printf("%s%d", f ? " " : "", i);
        f = true;
    }
    putchar(10);
}

bool judge() {
    bool is_liar[maxn] = {false};
    int num_liars = 0;
    for (int i = 1; i <= N; ++i) {
        if (statements[i] > 0 && !is_wolf[statements[i]] || statements[i] < 0 && is_wolf[-statements[i]])
            continue;
        is_liar[i] = true;
        num_liars++;
    }
    if (num_liars != L)return false;
    int lying_wolves = 0;
    for (int i = 1; i <= N; ++i) {
        if (is_wolf[i] && is_liar[i])lying_wolves++;
    }
    return lying_wolves >= 1 && lying_wolves < M;
}


void dfs(int wolf_cnt, int pos) {
    is_wolf[pos] = true;
    wolf_cnt++;
    if (wolf_cnt == M) {
        if(judge()){
            output_wolves();
            exit(0);
        }
    }else{
        for (int i = pos - 1; i > 0; --i) {
            dfs(wolf_cnt, i);
        }
    }
    wolf_cnt--;
    is_wolf[pos] = false;
}

void solve() {
    for (int i = N; i > 0; --i) {
        dfs(0, i);
    }
    puts("No Solution");
}

int main() {
//    freopen("Depressant.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}