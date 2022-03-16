#include "bits/stdc++.h"

std::string S, T;
typedef long long ll;
#define maxn 1005

void init() {

}

void read() {
    std::cin >> S >> T;
}

//dp[i][j]表示：字符串T中从下标i开始长度为j的子串作为S的子序列在S中的结束位置(如果不是S的子序列则值为-1)
int dp[maxn][maxn];


int compute() {
    int ans = 1;
    int char2FOpos[256];
    memset(char2FOpos, -1, sizeof char2FOpos);
    memset(dp, -1, sizeof dp);
    for (int i = 0; i < S.length(); ++i) {
        if (char2FOpos[S[i]] == -1)
            char2FOpos[S[i]] = i;
    }
    for (int i = 0; i < T.length(); ++i) {
        dp[i][1] = char2FOpos[T[i]];
    }
    for (int l = 2; l <= S.length(); ++l) {
        for (int i = 0; i <= S.length() - l; ++i) {
            if (dp[i][l - 1] != -1) {
                auto pos = std::find(S.begin() + dp[i][l - 1] + 1, S.end(), T[i + l - 1]);
                if (pos == S.end())
                    dp[i][l] = -1;
                else {
                    dp[i][l] = pos - S.begin();
                    ans = std::max(ans, l);
                }
            }
        }
    }
    return ans;
}

void solve() {
    printf("%d", S.length() - compute());
}

int main() {
//    freopen("Depressant.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}