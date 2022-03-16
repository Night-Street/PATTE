#include "bits/stdc++.h"

int N;
using namespace std;
#define maxn 10005
int color2value[maxn];
int idx2color[maxn];
int color2last[maxn];
int idx2last[maxn];
int dp[maxn];

int main() {
//    freopen("in.txt", "r", stdin);
    memset(color2last, -1, sizeof color2last);
    fill(begin(dp), end(dp), 1);
    cin >> N;
    for (int i = 0; i < N; i++) {
        scanf("%d", color2value + i + 1);
    }
    for (int i = 0; i < N; i++) {
        int color;
        scanf("%d", &color);
        idx2color[i] = color;
        idx2last[i] = color2last[color];
        color2last[color] = i;
    }
    int max_len = 1, max_value = color2value[idx2color[0]], ed = 0;
    for (int i = 1; i < N; i++) {
        int d = i - idx2last[i];
        if (idx2last[i] == -1 || d > dp[i - 1]) {
            dp[i] = dp[i - 1] + 1;
        } else {
            dp[i] = d;
        }
        if (dp[i] > max_len) {
            max_len = dp[i];
            ed = i;
            max_value = 0;
            for (int j = 0; j < dp[i]; j++) {
                max_value += color2value[idx2color[i - j]];
            }
        } else if (dp[i] == max_len) {
            int value = 0;
            for (int j = 0; j < dp[i]; j++) {
                value += color2value[idx2color[i - j]];
            }
            if (value > max_value) {
                max_value = value;
                ed = i;
            }
        }
    }

    printf("%d %d %d", max_value, ed - max_len + 1, ed);

    return 0;
}