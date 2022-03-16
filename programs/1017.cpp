#include <bits/stdc++.h>

using namespace std;
int N;
#define maxn 10005
int seq[maxn];
int lis[maxn] = {0}, lds[maxn] = {0};

void solve() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < i; ++j) {
            if (seq[j] < seq[i]) {
                lis[i] = max(lis[i], lis[j] + 1);
            }
        }
    }
    for (int i = N - 1; i >= 0; i--) {
        for (int j = N - 1; j > i; j--) {
            if (seq[j] < seq[i]) {
                lds[i] = max(lds[i], lds[j] + 1);
            }
        }
    }
    int len = -1, diff = INT_MAX, idx = -1;
    for (int i = 0; i < N; ++i) {
        if (lis[i] == 1 || lds[i] == 1)continue;
        int cur_len = lis[i] + lds[i] - 1;
        if (cur_len > len || cur_len == len && abs(lis[i] - lds[i]) < diff) {
            len = cur_len;
            idx = i;
        }
    }
    if (len == -1)puts("No peak shape");
    else printf("%d %d %d", len, idx + 1, seq[idx]);
}

int main() {
//    freopen("case.txt", "r", stdin);
    cin >> N;
    for (int i = 0; i < N; ++i) {
        scanf("%d", seq + i);
        lis[i] = lds[i] = 1;
    }
    solve();
    return 0;
}