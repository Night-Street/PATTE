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

void solve() {

}

int main() {
    freopen("Depressant.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}