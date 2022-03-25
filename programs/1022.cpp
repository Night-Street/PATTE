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
//存储各名玩家说过的话(用正数或负数表示)
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
/**
 * 降序输出所有狼人玩家的编号
 */
void output_wolves() {
    bool f = false;
    for (int i = N; i > 0; --i) {
        if (!is_wolf[i])continue;
        printf("%s%d", f ? " " : "", i);
        f = true;
    }
    putchar(10);
}
/**
 * 判断当前解的合法性
 * @return 合法返回true，非法返回false
 */
bool judge() {
//    统计说谎的玩家有哪些
    bool is_liar[maxn] = {false};
//    统计说谎玩家的总数
    int num_liars = 0;
    for (int i = 1; i <= N; ++i) {
//        遍历每一位玩家的发言，如果与事实不符则视为说谎
        if (statements[i] > 0 && !is_wolf[statements[i]] || statements[i] < 0 && is_wolf[-statements[i]])
            continue;
        is_liar[i] = true;
        num_liars++;
    }
//    如果说谎人数不等于L，则此解非法
    if (num_liars != L)return false;
    int lying_wolves = 0;
    for (int i = 1; i <= N; ++i) {
        if (is_wolf[i] && is_liar[i])lying_wolves++;
    }
//    说谎的狼人玩家数在[1,M)内时才算合法
    return lying_wolves >= 1 && lying_wolves < M;
}

/**
 * 搜索所有可能的狼人玩家组合
 * @param wolf_cnt 目前状态下的狼人玩家数量
 * @param pos 下一步即将搜索的玩家编号
 */
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