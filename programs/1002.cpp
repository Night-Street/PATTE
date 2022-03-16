#include <bits/stdc++.h>
#define rg(i, a, b) for(auto i = a; i != b; i++)
#define until(s) while(!(s))
using namespace std;
#define maxn 55
int profit[maxn];
int lasting_day[maxn];
int deadline[maxn];
int dp[maxn][1005] = { 0 };
int project[maxn];
int N;
int main() {
    cin >> N;
    int max_deadline = 0;
    rg(i, 1, N + 1) {
        project[i] = i;
        scanf("%d%d%d", &profit[i], &lasting_day[i], &deadline[i]);
        max_deadline = max(max_deadline, deadline[i]);
    }
    sort(project + 1, project + N + 1, [&](int i1, int i2) {
        return deadline[i1] < deadline[i2];
    });

    rg(i, 1, N + 1) {
        rg(j, 1, max_deadline + 1) {
            int cur_project = project[i];
            if (j - lasting_day[cur_project] >= 0 && j <= deadline[cur_project] && dp[i - 1][j - lasting_day[cur_project]] + profit[cur_project] > dp[i - 1][j]) {
                dp[i][j] = dp[i - 1][j - lasting_day[cur_project]] + profit[cur_project];
            } else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }
    cout << *max_element(dp[N], dp[N] + max_deadline + 1);
    return 0;
}
