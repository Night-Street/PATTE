/*
    Data Structure and Algorithm.
    Created by CLion
    Author: Depressant
    Date: 2022.4.26
    Time: 下午 10:03
*/
#include "bits/stdc++.h"

#define maxn 100005
typedef long long ll;
int N;
ll cnt = 0;
int arr[maxn];

struct FenwickTree {
    int len{};
    std::vector<ll> _v;


    void setLen(int l) {
        len = l;
        _v.resize(l + 1);
    }

    static int lowbit(int x) { return x & (-x); }

    void update(int pos, ll val) {
        while (pos <= len) {
            _v[pos] += val;
            pos += lowbit(pos);
        }
    }

    ll query(int pos) {
        ll ret = 0;
        while (pos > 0) {
            ret += _v[pos];
            pos -= lowbit(pos);
        }
        return ret;
    }
};

FenwickTree ft1, ft2;

void init() {

}

void read() {
    std::cin >> N;
    for (int i = 0; i < N; ++i) {
        scanf("%d", &arr[i]);
    }
    ft1.setLen(N);
    ft2.setLen(N);
}

void solve() {
    for (int i = N - 1; i >= 0; --i) {
        ll tmp = ft1.query(arr[i] - 1);
        ft1.update(arr[i], 1);
        cnt += ft2.query(arr[i] - 1);
        ft2.update(arr[i], tmp);
    }
    std::cout << cnt;
}

int main() {
//    freopen("Depressant.txt", "r", stdin);
    init();
    read();
    solve();
    return 0;
}