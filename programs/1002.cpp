/*
    Data Structure and Algorithm.
    Created by CLion.
    Author: Depressant
    Date: 2022.3.25
    Time: 下午 3:28
*/
#include "bits/stdc++.h"

#define maxn 55
int P[maxn], L[maxn], D[maxn];
//所有工程中deadline的最大值
int max_ddl = 0;
int N;
typedef long long ll;
//由于要将所有工程按deadline升序排序，所以要用vector存储每个工程的编号
std::vector<int> projects;
int dp[maxn][1005];

void init() {

}

void read() {
    std::cin >> N;
    for (int i = 1; i <= N; ++i) {
        scanf("%d%d%d", &P[i], &L[i], &D[i]);
        max_ddl = std::max(max_ddl, D[i]);
        projects.push_back(i);
    }
}

void solve() {
//    将所有工程按deadline升序排序
    std::sort(projects.begin(), projects.end(), [&](int i, int j) {
        return D[i] < D[j];
    });
    projects.insert(projects.begin(), 0);
//    dp搜索最优解过程
    for (int i = 1; i <= N; ++i) {
        int cur_project = projects[i];
        for (int j = 1; j <= max_ddl; ++j) {
            if (j - L[cur_project] >= 0 && j <= D[cur_project] &&
                dp[i][j] < P[cur_project] + dp[i - 1][j - L[cur_project]]) {
                dp[i][j] = std::max(dp[i - 1][j], P[cur_project] + dp[i - 1][j - L[cur_project]]);
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
//    输出最优解
    std::cout << *std::max_element(dp[N], dp[N] + max_ddl + 1);
}

int main() {
//    freopen("Depressant.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}